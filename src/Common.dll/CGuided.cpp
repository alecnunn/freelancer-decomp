// CGuided -- a guided munition (missile) in flight. Derives from CSimple.
// Recovered from Common.dll. Symbol-rich unit: real member definitions mangle
// to the original symbols and pair automatically.
//
// Relevant layout:
//   +0x88  const Archetype::Munition*  m_arch    (guidance in arch->guidance)
//   +0xf0  char*                       m_target  (watched ptr; get_target - 8)
//   +0xf8  unsigned short              m_sub_target
#include "common.h"
#include "archetype.h"

struct IObjRW;

class CGuided {
public:
    unsigned char               _pad_0[0x88];          // CSimple base
    const Archetype::Munition*  m_arch;                // +0x88
    unsigned char               _pad_8c[0xf0 - 0x8c];  // +0x8c .. +0xf0
    char*                       m_target;              // +0xf0  (BaseWatcher.m_watched)
    unsigned char               _pad_f4[4];            // +0xf4  (BaseWatcher.m_next)
    unsigned short              m_sub_target;          // +0xf8

    IObjRW* get_target() const;
    unsigned short get_sub_target() const;
    void set_sub_target(unsigned short t);
};

IObjRW* CGuided::get_target() const {
    if (m_target != 0)
        return (IObjRW*)(m_target - 8);
    return 0;
}

unsigned short CGuided::get_sub_target() const {
    return m_sub_target;
}

void CGuided::set_sub_target(unsigned short t) {
    if (m_arch->guidance != 0)
        m_sub_target = t;
}
