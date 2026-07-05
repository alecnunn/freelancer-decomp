// CLoot -- a dropped loot/cargo container. Derives CObject<-CLoot; own fields
// from 0xe4. Modeled flat; the leading pad includes the vftable pointer so
// fields land at their real offsets.
#include "common.h"

namespace Archetype { struct Equipment; }

struct CLoot {
    unsigned char _pad_0x00[0xe4];      // +0x00 .. +0xe4  vftable + CObject base
    unsigned int  m_owner;              // +0xe4
    unsigned char _pad_0xe8[4];         // +0xe8  (container arch)
    Archetype::Equipment* m_contents_arch; // +0xec
    unsigned int  m_units;              // +0xf0
    float         m_contents_hit_pts;   // +0xf4
    unsigned char _pad_0xf8[4];         // +0xf8
    bool          m_can_ai_tractor;     // +0xfc
    bool          m_is_loot_temporary;  // +0xfd

    unsigned int get_owner() const;
    Archetype::Equipment* contents_arch() const;
    unsigned int get_units() const;
    float get_contents_hit_pts() const;
    float get_volume() const;
    bool can_ai_tractor() const;
    bool is_loot_temporary() const;
};

unsigned int CLoot::get_owner() const { return m_owner; }
Archetype::Equipment* CLoot::contents_arch() const { return m_contents_arch; }
unsigned int CLoot::get_units() const { return m_units; }
float CLoot::get_contents_hit_pts() const { return m_contents_hit_pts; }
float CLoot::get_volume() const {
    return (float)m_units * *(const float*)((const char*)m_contents_arch + 0x5c);
}
bool CLoot::can_ai_tractor() const { return m_can_ai_tractor; }
bool CLoot::is_loot_temporary() const { return m_is_loot_temporary; }
