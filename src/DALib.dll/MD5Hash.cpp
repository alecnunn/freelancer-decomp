// DALib.dll -- MD5 message-digest (RSA Data Security reference implementation).
// Recovered from DALib.dll; symbol-rich, so the real member definitions mangle
// to the original symbols and objdiff pairs them automatically.
//
// Layout (from the ctor / GetStatePtr):
//   +0x00  vptr
//   +0x04  unsigned int  m_state[4]    (a,b,c,d; init to the MD5 IVs)
//   +0x14  unsigned int  m_count[2]    (message length in bits, lo/hi)
//   +0x1c  unsigned char m_buffer[64]  (input block)
//   +0x5c  bool          m_finalized
#include "DALib.h"
#include <string.h>   // memcmp (intrinsic under /Oi)
#include <stdio.h>    // sprintf

MD5Hash::MD5Hash() {
    m_count[1] = 0;
    m_count[0] = 0;
    m_state[0] = 0x67452301;
    m_state[1] = 0xefcdab89;
    m_state[2] = 0x98badcfe;
    m_state[3] = 0x10325476;
    m_string[0] = 0;
}

MD5Hash::~MD5Hash() {}

unsigned char* MD5Hash::GetStatePtr() {
    return (unsigned char*)m_state;
}

bool MD5Hash::Compare(MD5Hash& other) {
    return memcmp(m_state, other.m_state, 16) == 0;
}

const char* MD5Hash::AsString() {
    sprintf(m_string, "%08x%08x%08x%08x", m_state[0], m_state[1], m_state[2], m_state[3]);
    return m_string;
}

void MD5Hash::FromString(const char* str) {
    sscanf(str, "%08x%08x%08x%08x", &m_state[0], &m_state[1], &m_state[2], &m_state[3]);
}

// Encode: pack an array of UINT4 into bytes, little-endian. (RSA reference.)
// 75.5%: correct; the original optimizes the little-endian shifts into a byte
// copy (mov dl,[ecx-2]...), which MSVC6 doesn't reproduce from either the shift
// or byte-index form here.
void MD5Hash::Encode(unsigned char* output, unsigned long* input, unsigned long len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[j]     = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

// Decode: unpack bytes into UINT4, little-endian. (RSA reference.)
void MD5Hash::Decode(unsigned long* output, unsigned char* input, unsigned long len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j + 1]) << 8) |
                    (((unsigned int)input[j + 2]) << 16) | (((unsigned int)input[j + 3]) << 24);
}
