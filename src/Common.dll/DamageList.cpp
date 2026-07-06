// DamageList -- accumulates per-sub-object damage records during a combat
// resolution pass, plus overall cause/destroyed/inflictor state.
// Recovered from Common.dll; size 0x1C. Symbol-rich unit: real member
// functions mangle to the original symbols and pair automatically.
//
// The class embeds a std::list<DamageEntry> at +0x00 (node size 0x14). As with
// the other STL-bearing classes in this unit (see Archetype_CollisionGroup),
// the list is modeled as a raw 12-byte blob so the POD tail lands at the right
// offsets. Every function that manipulates the list -- the default ctor (list
// sentinel construction), the compiler-generated copy-ctor / copy-assign (deep
// list copy), add_damage_entry, and get_hit_pts_left -- is deferred: matching
// them requires the exact MSVC6 std::list<DamageEntry> instantiation. Only
// is_inflictor_a_player touches nothing but the POD tail and is implemented here.
#include "common.h"

struct DamageList {
    unsigned char m_entries[12];  // +0x00  std::list<DamageEntry> (node 0x14)
    bool          m_destroyed;    // +0x0c
    unsigned char _pad_d[3];      // +0x0d
    int           m_cause;        // +0x10  DamageCause
    int           m_field14;      // +0x14
    int           m_inflictor;    // +0x18  inflictor handle (nonzero => a player)

    bool is_inflictor_a_player() const;
};

bool DamageList::is_inflictor_a_player() const { return m_inflictor != 0; }
