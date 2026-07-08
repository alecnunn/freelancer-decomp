// x86math.dll -- fast reciprocal square root (Quake-style bit hack).
// A 1024-entry seed table is precomputed at startup: for each 10-bit mantissa
// index, reconstruct a float, take 1/sqrt, and store a byte of the result's
// mantissa. The rsqrt routines then form a seed from the input's exponent (via
// the 0x5f000000 magic) plus a table lookup, and refine it with Newton steps.
#include "x86math.h"

extern "C" char __delink_ida_data_start[];    // rsqrt seed table lives at +0x30
extern "C" char __delink_ida_const_start[];   // 1.0 (double) at +0x44

extern "C" double __cdecl sqrt(double);       // intrinsic under /Oi -> fsqrt

// sub_6F71010: build the 1024-entry rsqrt seed table. 99.7% -- the only diff is
// `or ecx,0xfc00` vs the original's 2-byte `or ch,0xfc` (a size idiom; the /Os
// pragma reproduces that op but regresses the rest of the loop, so not worth it).
extern "C" void __cdecl x86m_init_rsqrt_table() {
    unsigned char* table = (unsigned char*)(__delink_ida_data_start + 0x30);
    int i;
    for (i = 0; i < 0x400; i++) {
        float in, out;
        *(unsigned int*)&in = (i | 0xfc00) << 14;
        out = (float)(*(const double*)(__delink_ida_const_start + 0x44) / sqrt(in));
        table[i] = (unsigned char)((*(unsigned int*)&out + 0x2000) >> 15);
    }
    table[0x200] = 0xff;
}

// sub_6F72830: *out = 1/sqrt(x). Form a seed from x's exponent (0x5f000000 magic)
// plus the mantissa lookup, then refine with two Newton-Raphson iterations
// y = y * (C1 - x*y*y) * C2  (C1 = 3.0, C2 = 0.5).
// ~70%: logic + the seed bit-hack + Newton steps are correct; residuals are all
// MSVC codegen we can't steer from source -- it reassociates the two trailing
// fmuls (*y / *C2 order) and strength-reduces the exponent extract
// (`(xb>>23)&0xff)<<22` -> `(xb>>1)&0x3fc00000`).
extern "C" void __stdcall x86m_rsqrt(void* /*self*/, float* out, float x) {
    unsigned char* table = (unsigned char*)(__delink_ida_data_start + 0x30);
    unsigned int xb = *(unsigned int*)&x;
    unsigned int exp = (xb >> 23) & 0xff;
    unsigned int seed_bits = ((0x5f000000 - (exp << 22)) & 0xff800000)
                           | ((unsigned int)table[(xb >> 14) & 0x3ff] << 15);
    float y = *(float*)&seed_bits;
    float y1 = (*(const float*)(__delink_ida_const_start + 0xd4) - y * y * x) * y
             * *(const float*)(__delink_ida_const_start + 0xcc);
    *out = (*(const float*)(__delink_ida_const_start + 0xd4) - y1 * y1 * x) * y1
         * *(const float*)(__delink_ida_const_start + 0xcc);
}

// sub_6F728B0: *out = sqrt(x), computed as rsqrt(x) * x (same seed + 2 Newton
// steps, then one extra multiply by x). Same ~70% codegen cap as x86m_rsqrt.
extern "C" void __stdcall x86m_sqrt_via_rsqrt(void* /*self*/, float* out, float x) {
    unsigned char* table = (unsigned char*)(__delink_ida_data_start + 0x30);
    unsigned int xb = *(unsigned int*)&x;
    unsigned int exp = (xb >> 23) & 0xff;
    unsigned int seed_bits = ((0x5f000000 - (exp << 22)) & 0xff800000)
                           | ((unsigned int)table[(xb >> 14) & 0x3ff] << 15);
    float y = *(float*)&seed_bits;
    float y1 = (*(const float*)(__delink_ida_const_start + 0xd4) - y * y * x) * y
             * *(const float*)(__delink_ida_const_start + 0xcc);
    *out = (*(const float*)(__delink_ida_const_start + 0xd4) - y1 * y1 * x) * y1
         * *(const float*)(__delink_ida_const_start + 0xcc) * x;
}

