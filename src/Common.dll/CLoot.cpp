// CLoot -- a dropped loot/cargo container. Derives CObject<-CSimple<-CLoot; own
// fields from +0xe4 (CSimple's size). CSimple is defined earlier in the unity
// build. The container archetype is fetched via CAsteroid::asteroidarch.
#include "common.h"
#include "archetype.h"

extern "C" __declspec(dllimport) char* __cdecl itoa(int value, char* buf, int radix);
extern "C" char _delink_ida_const_start[];   // delinked read-only const blob
namespace PhySys { void SetCollisionGroup(CObject* obj, const char* const group); }

struct CLoot : CSimple {
    unsigned int  m_owner;              // +0xe4
    unsigned int  m_name;               // +0xe8  explicit name id (0 = use arch)
    Archetype::Equipment* m_contents_arch; // +0xec
    unsigned int  m_units;              // +0xf0
    float         m_contents_hit_pts;   // +0xf4
    float         m_safe_time;          // +0xf8  owner-only tractor grace time
    bool          m_can_ai_tractor;     // +0xfc
    bool          m_is_loot_temporary;  // +0xfd

    unsigned int get_owner() const;
    Archetype::Equipment* contents_arch() const;
    unsigned int get_units() const;
    void set_units(unsigned int units);
    float get_contents_hit_pts() const;
    void set_contents_hit_pts(float hp);
    float get_volume() const;
    bool can_ai_tractor() const;
    bool is_loot_temporary() const;
    virtual unsigned int get_name() const;
    virtual int update(float dt, unsigned int flags);
};

unsigned int CLoot::get_owner() const { return m_owner; }
Archetype::Equipment* CLoot::contents_arch() const { return m_contents_arch; }
unsigned int CLoot::get_units() const { return m_units; }
void CLoot::set_units(unsigned int units) { m_units = units; }
float CLoot::get_contents_hit_pts() const { return m_contents_hit_pts; }
void CLoot::set_contents_hit_pts(float hp) { m_contents_hit_pts = hp; }
float CLoot::get_volume() const {
    return (float)m_units * m_contents_arch->volume;
}
bool CLoot::can_ai_tractor() const { return m_can_ai_tractor; }
bool CLoot::is_loot_temporary() const { return m_is_loot_temporary; }

unsigned int CLoot::get_name() const {
    unsigned int n = m_name;
    if (n != 0)
        return n;
    return m_contents_arch->id_name;
}

// Per-frame: run zone logic, count down the owner-only tractor grace period
// (resetting the collision group to the instance id when it expires), then the
// base object update.
int CLoot::update(float dt, unsigned int flags) {
    CSimple::update_zones(dt, flags);
    if (m_safe_time > *(const float*)(_delink_ida_const_start + 0x54)) {
        m_safe_time -= dt;
        if (m_safe_time <= *(const float*)(_delink_ida_const_start + 0x54)) {
            char buf[8];
            itoa(m_id, buf, 0x18);
            PhySys::SetCollisionGroup(this, buf);
        }
    }
    CObject::update(dt, flags);
    return 0;
}
