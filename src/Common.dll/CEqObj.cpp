// CEqObj -- equipment-carrying simulatable object; base of CShip/CSolar.
// Derives CObject <- CSimple <- CEqObj (own fields from ~0x104). Modeled flat
// here (offset-based bodies); only offsets touched by matched methods are named.
#include "common.h"

class IBehaviorManager;

struct CEqObj {
    // vftable ptr + EngineObject/CObject/CSimple base subobjects fill 0x00..0x104.
    unsigned char _pad_0x00[0x104];  // +0x00 .. +0x104
    int           m_vibe;            // +0x104
    unsigned char _pad_0x108[0x38];  // +0x108 .. +0x140
    float         m_cloak;           // +0x140  (>= 1.0 == cloaked)
    unsigned char _pad_0x144[0x1c];  // +0x144 .. +0x160
    unsigned int  m_base;            // +0x160
    unsigned int  m_dock_target;     // +0x164
    unsigned char _pad_0x168[0x28];  // +0x168 .. +0x190
    unsigned int  m_control_exclusion; // +0x190
    IBehaviorManager* m_behavior;    // +0x194
    float         m_power;           // +0x198
    float         m_max_power;       // +0x19c

    int get_vibe() const;
    void set_power(float power);
    void set_control_exclusion(unsigned int mask);
    bool is_control_excluded(unsigned int mask) const;
    IBehaviorManager* get_behavior_interface();
    int is_cloaked() const;
    float get_cloak_percentage() const;
    bool is_base() const;
    bool is_dock() const;
    unsigned int get_base() const;
    const unsigned int& get_dock_target() const;
    float get_power() const;
    float get_max_power() const;
    float get_power_ratio() const;
};

int CEqObj::get_vibe() const { return m_vibe; }
void CEqObj::set_power(float power) { m_power = power; }
void CEqObj::set_control_exclusion(unsigned int mask) { m_control_exclusion = mask; }
bool CEqObj::is_control_excluded(unsigned int mask) const { return (m_control_exclusion & mask) != 0; }
IBehaviorManager* CEqObj::get_behavior_interface() { return m_behavior; }
int CEqObj::is_cloaked() const {
    if (m_cloak >= 1.0f)
        return 1;
    return 0;
}
float CEqObj::get_cloak_percentage() const { return m_cloak; }
bool CEqObj::is_base() const { return m_base != 0; }
bool CEqObj::is_dock() const { return m_dock_target != 0; }
unsigned int CEqObj::get_base() const { return m_base; }
const unsigned int& CEqObj::get_dock_target() const { return m_dock_target; }
float CEqObj::get_power() const { return m_power; }
float CEqObj::get_max_power() const { return m_max_power; }
float CEqObj::get_power_ratio() const {
    if (m_max_power <= 0.0f)
        return 0.0f;
    return m_power / m_max_power;
}
