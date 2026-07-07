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
