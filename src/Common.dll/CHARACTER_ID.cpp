// CHARACTER_ID -- a case-insensitive string identifier for a character.
// Recovered from Common.dll. Symbol-rich unit: real member/free functions
// mangle to the original symbols and objdiff pairs them automatically.
//
// The type is a plain NUL-terminated char buffer: the constructor and
// invalidate() clear byte 0, is_valid() tests byte 0, and the comparison
// operators forward the buffer straight to stricmp() (the CHARACTER_ID& decays
// to char* at offset 0). operator= is a hand-written strcpy loop. Because none
// of these functions index past byte 0 (and the copy is a strcpy, not a fixed
// memcpy), the total buffer size is not recoverable from- and does not affect-
// the emitted code; a plausible fixed size is used here.
#include "common.h"  // provides stricmp via <string.h>

struct CHARACTER_ID {
    char m_id[64];

    CHARACTER_ID();

    bool is_valid() const;
    void invalidate();

    const CHARACTER_ID& operator=(const CHARACTER_ID& o);
};

bool operator==(const CHARACTER_ID& a, const CHARACTER_ID& b);
bool operator!=(const CHARACTER_ID& a, const CHARACTER_ID& b);
bool operator<(const CHARACTER_ID& a, const CHARACTER_ID& b);

CHARACTER_ID::CHARACTER_ID() {
    m_id[0] = 0;
}

void CHARACTER_ID::invalidate() {
    m_id[0] = 0;
}

bool CHARACTER_ID::is_valid() const {
    return m_id[0] != 0;
}

const CHARACTER_ID& CHARACTER_ID::operator=(const CHARACTER_ID& o) {
    char* dst = m_id;
    const char* src = o.m_id;
    while ((*dst++ = *src++) != '\0')
        ;
    return *this;
}

bool operator==(const CHARACTER_ID& a, const CHARACTER_ID& b) {
    return stricmp(a.m_id, b.m_id) == 0;
}

bool operator!=(const CHARACTER_ID& a, const CHARACTER_ID& b) {
    return stricmp(a.m_id, b.m_id) != 0;
}

bool operator<(const CHARACTER_ID& a, const CHARACTER_ID& b) {
    return stricmp(a.m_id, b.m_id) < 0;
}
