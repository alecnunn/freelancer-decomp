// x86math.dll -- 3x3 matrix / vector transform routines.
// These are __stdcall functions with the engine `this` passed as an unused
// leading stack slot, then (out, matrix, vector). Each computes out = M * v
// row by row (out.c = M.row_c . v). All unnamed (sub_XXX); claimed to the C++
// symbols below.
#include "x86math.h"

// sub_6F71830: out = M * v   (rotate a vector by a 3x3 matrix)
// 93.8%: correct; the residual is a /G6 scheduling cap -- the original groups
// all three pointer loads (M, v, out) before the FP, MSVC6 here defers the out
// load past the first fmul. Same class as the loop-head-align caps.
extern "C" int __stdcall x86m_rotate(int /*self*/, Vector* out, const Matrix* M, const Vector* v) {
    out->x = M->m[0] * v->x + M->m[1] * v->y + M->m[2] * v->z;
    out->y = M->m[3] * v->x + M->m[4] * v->y + M->m[5] * v->z;
    out->z = M->m[6] * v->x + M->m[7] * v->y + M->m[8] * v->z;
    return 0;
}
