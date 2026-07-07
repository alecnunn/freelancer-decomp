// CProjectile -- a fired bullet/projectile. Derives from CSimple.
// Recovered from Common.dll. Symbol-rich unit: real member definitions mangle
// to the original symbols and pair automatically.
//
// Relevant layout:
//   +0xe4  unsigned int  m_owner            (owning object id)
//   +0xe8  float         m_lifetime         (< 0 == dead; set_dead writes -1.0)
//   +0xec  float         m_owner_safe_time  (grace period vs. own launcher)
#include "common.h"

extern "C" char _delink_ida_const_start[];   // delinked read-only const blob (+0x54 == 0.0f)

class CProjectile {
public:
    virtual void set_dead();            // vtable slot; vptr at +0x00

    unsigned char _pad_4[0xe4 - 4];     // +0x04 .. +0xe4
    unsigned int  m_owner;              // +0xe4
    float         m_lifetime;           // +0xe8
    float         m_owner_safe_time;    // +0xec

    const unsigned int& get_owner() const;
    bool is_alive() const;
};

void CProjectile::set_dead() {
    m_lifetime = -1.0f;
}

const unsigned int& CProjectile::get_owner() const {
    return m_owner;
}

bool CProjectile::is_alive() const {
    return m_lifetime >= *(const float*)(_delink_ida_const_start + 0x54);
}
