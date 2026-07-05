// CEShield -- a mounted shield generator. Hierarchy
// CEquip<-CExternalEquip<-CAttachedEquip<-CEShield; own fields from ~0x4c.
// Modeled flat; the first 5 vtable slots are declared in order so
// IsFunctioning's self-dispatch emits the right vtable offsets.
#include "common.h"

namespace Archetype { struct ShieldGenerator; }

struct CEShield {
    // vftable ptr at +0x00
    unsigned char _pad_0x04[0x48];   // +0x04 .. +0x4c
    unsigned char m_connected;       // +0x4c  connected/active state (byte)
    unsigned char _pad_0x4d[3];      // +0x4d
    float         m_hit_pts;         // +0x50  current shield hit points
    unsigned char _pad_0x54[0x1c];   // +0x54 .. +0x70
    Archetype::ShieldGenerator* m_gen_arch; // +0x70
    float         m_offline_threshold;      // +0x74
    float         m_offline_rebuild_time;   // +0x78
    float         m_max_hit_pts;            // +0x7c

    // virtuals declared in slot order (0-4 load-bearing for IsFunctioning)
    virtual ~CEShield();                 // slot 0
    virtual bool IsActive() const;       // slot 1  (byte 0x04)
    virtual bool IsDestroyed() const;    // slot 2  (byte 0x08)
    virtual bool IsFunctioning() const;  // slot 3  (byte 0x0c)
    virtual bool _is_disabled() const;   // slot 4  (byte 0x10)
    virtual float GetMaxHitPoints() const;

    float GetOfflineThreshold() const;
    float GetOfflineRebuildTime() const;
    Archetype::ShieldGenerator* ShieldGenArch() const;
};

CEShield::~CEShield() {}
bool CEShield::IsActive() const { return false; }      // placeholder (inherited slot)
bool CEShield::IsDestroyed() const { return false; }   // placeholder
bool CEShield::_is_disabled() const { return false; }  // placeholder
bool CEShield::IsFunctioning() const {
    return IsActive() && !_is_disabled() && !IsDestroyed() && m_connected != 0;
}
float CEShield::GetMaxHitPoints() const { return m_max_hit_pts; }
float CEShield::GetOfflineThreshold() const { return m_offline_threshold; }
float CEShield::GetOfflineRebuildTime() const { return m_offline_rebuild_time; }
Archetype::ShieldGenerator* CEShield::ShieldGenArch() const { return m_gen_arch; }
