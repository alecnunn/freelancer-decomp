// Archetype data structs -- the static equipment/object definitions that the
// runtime objects point at via m_arch. Read-only pointees. Root owns the
// vftable (via get_class_type), so every derived archetype shares one vptr@0
// and consistent field offsets. Named member access compiles to the same
// offset load as a raw cast; the field offsets are the load-bearing part.
#ifndef COMMON_DLL_ARCHETYPE_H
#define COMMON_DLL_ARCHETYPE_H

#include "common.h"   // Archetype::AClassType

namespace Archetype {

// Common archetype base. Abstract: each concrete archetype overrides
// get_class_type() to return its constant AClassType tag.
struct Root {
    // vftable ptr @ +0x00 (from the virtual below)
    unsigned char _pad_0x04[4];    // +0x04
    unsigned int  good_id;         // +0x08  good/nickname hash
    unsigned char _pad_0x0c[4];    // +0x0c
    unsigned int  class_type;      // +0x10  runtime class tag (data)
    unsigned char _pad_0x14[8];    // +0x14
    float         hit_pts;         // +0x1c  max hit points
    float         mass;            // +0x20
    unsigned char _pad_0x24[0x38]; // +0x24 .. +0x5c
    float         volume;          // +0x5c  cargo volume
    unsigned char _pad_0x60[0xc];  // +0x60 .. +0x6c
    int           lootable;        // +0x6c
    virtual AClassType get_class_type() const = 0;   // vtable slot 0
};

// --- Concrete archetypes tagged with a get_class_type (bodies in
//     Archetype_class_types.cpp). Extend any of them with named fields as
//     those layouts are recovered. ---
struct Asteroid              : Root { virtual AClassType get_class_type() const; };
struct DynamicAsteroid       : Root { virtual AClassType get_class_type() const; };
struct Equipment             : Root {
    unsigned char _pad_0x70[0x14];   // +0x70 .. +0x84
    int           toughness;         // +0x84  loot/debris toughness
    virtual AClassType get_class_type() const;
};
struct AttachedEquipment     : Root { virtual AClassType get_class_type() const; };
struct LootCrate             : Root { virtual AClassType get_class_type() const; };
struct Thruster              : Root { virtual AClassType get_class_type() const; };
struct Launcher              : Root { virtual AClassType get_class_type() const; };
struct Gun                   : Root { virtual AClassType get_class_type() const; };
struct CounterMeasureDropper : Root { virtual AClassType get_class_type() const; };
struct Scanner               : Root { virtual AClassType get_class_type() const; };
struct Light                 : Root { virtual AClassType get_class_type() const; };
struct Tractor               : Root { virtual AClassType get_class_type() const; };
struct AttachedFXEquip       : Root { virtual AClassType get_class_type() const; };
struct InternalFXEquip       : Root { virtual AClassType get_class_type() const; };
struct RepairDroid           : Root { virtual AClassType get_class_type() const; };
struct RepairKit             : Root { virtual AClassType get_class_type() const; };
struct ShieldBattery         : Root { virtual AClassType get_class_type() const; };
struct CloakingDevice        : Root { virtual AClassType get_class_type() const; };
struct Projectile            : Root { virtual AClassType get_class_type() const; };
struct Munition              : Root {
    unsigned char _pad_0x70[0x20];   // +0x70 .. +0x90
    int           guidance;          // +0x90  guidance type (0 = unguided)
    virtual AClassType get_class_type() const;
};
struct Mine                  : Root { virtual AClassType get_class_type() const; };
struct CounterMeasure        : Root { virtual AClassType get_class_type() const; };
struct Armor                 : Root { virtual AClassType get_class_type() const; };

// --- Data archetypes with recovered fields (not separately get_class_type-
//     tagged in the delink; abstract, used only as typed pointees). ---

// Engine archetype (thrust/drag/cruise parameters).
struct Engine : Root {
    float         max_force;          // +0x70
    float         linear_drag;        // +0x74
    unsigned char _pad_0x78[4];       // +0x78
    float         cruise_power_draw;  // +0x7c
    float         cruise_charge_time; // +0x80
    unsigned char _pad_0x84[4];       // +0x84
    float         cruise_speed;       // +0x88
};

// Shield-generator archetype (fields TBD; type needed for ShieldGenArch()).
struct ShieldGenerator : Root { };

// Ship archetype (flyable-ship parameters).
struct Ship : Root {
    unsigned char _pad_0x70[0xbc];   // +0x70 .. +0x12c
    float         max_bank_angle;    // +0x12c
};

} // namespace Archetype

#endif // COMMON_DLL_ARCHETYPE_H
