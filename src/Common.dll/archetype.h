// Archetype data structs -- the static equipment/object definitions that the
// runtime objects point at via m_arch. Read-only pointees: the vftable pointer
// is modeled as leading padding (we never construct these here). Field offsets
// are load-bearing; named access compiles to the same offset load as a raw cast.
#ifndef COMMON_DLL_ARCHETYPE_H
#define COMMON_DLL_ARCHETYPE_H

namespace Archetype {

// Common archetype base (Root). Extend as fields are recovered.
struct Root {
    unsigned char _vtbl_pad[8];    // +0x00  vftable ptr (+ pad)
    unsigned int  good_id;         // +0x08  good/nickname hash
    unsigned char _pad_0x0c[4];    // +0x0c
    unsigned int  class_type;      // +0x10  runtime class tag
    unsigned char _pad_0x14[8];    // +0x14
    float         hit_pts;         // +0x1c  max hit points
    float         mass;            // +0x20
    unsigned char _pad_0x24[0x38]; // +0x24 .. +0x5c
    float         volume;          // +0x5c  cargo volume
    unsigned char _pad_0x60[0xc];  // +0x60 .. +0x6c
    int           lootable;        // +0x6c
    // size 0x70
};

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

} // namespace Archetype

#endif // COMMON_DLL_ARCHETYPE_H
