// Common.dll -- shared type declarations recovered from the original binary.
//
// These types are referenced across many translation units in the unity build.
// Keep layouts byte-exact: field offsets are load-bearing for matching.
#ifndef COMMON_DLL_COMMON_H
#define COMMON_DLL_COMMON_H

// Standard headers used across the unity TU. Including them once here keeps
// individual class files from redeclaring CRT/placement-new symbols (which
// clash when another file pulls in <vector>/<new>/<string.h>).
#include <new>
#include <string.h>
#include <stdlib.h>

// A hashed string handle. Freelancer stores strings as a single 32-bit id.
// Size 4; assigned/compared as a plain dword by the original codegen.
struct CacheString {
    unsigned int id;
};

// An interned identifier string (nickname hash). Size 4.
struct ID_String {
    unsigned int id;
};

// Global constant: the "no sub-object" id sentinel (?SUBOBJ_ID_NONE@@3GB).
extern const unsigned short SUBOBJ_ID_NONE;

// Core math types (mangle as class 'V'). Layouts are load-bearing.
class Vector {      // size 0x0c
public:
    float x;
    float y;
    float z;
};

class Matrix {      // size 0x24  (row-major 3x3)
public:
    float d[3][3];
};

class Transform {   // size 0x30  (orientation then position)
public:
    Matrix orientation;
    Vector position;
};

// Per-hardpoint record held by HardpointSummary (mangles as struct 'U').
// Opaque 0x48-byte blob until its fields are recovered.
struct HardpointInfo {  // size 0x48
    unsigned char _pad[0x48];
};

// ObjectType -- the space-object classification bitmask stored in
// CSimple::m_type (@0xe0) and returned by CSimple::get_type(). Each object is
// tagged with one or more of these bits; predicates test masks of them. Bits
// 0-2/6/7/9/10/11 are verified against the recovered CSolar predicates; the
// remainder are the standard Freelancer ObjectType values.
enum ObjectType {
    OBJ_NONE              = 0x00000000,
    OBJ_MOON              = 0x00000001,
    OBJ_PLANET            = 0x00000002,
    OBJ_SUN               = 0x00000004,
    OBJ_BLACK_HOLE        = 0x00000008,
    OBJ_SATELLITE         = 0x00000010,
    OBJ_DOCKING_RING      = 0x00000020,
    OBJ_JUMP_GATE         = 0x00000040,
    OBJ_TRADELANE_RING    = 0x00000080,
    OBJ_STATION           = 0x00000100,
    OBJ_WAYPOINT          = 0x00000200,
    OBJ_AIRLOCK_GATE      = 0x00000400,
    OBJ_JUMP_HOLE         = 0x00000800,
    OBJ_WEAPONS_PLATFORM  = 0x00001000,
    OBJ_DESTROYABLE_DEPOT = 0x00002000,
    OBJ_NON_TARGETABLE    = 0x00004000,
    OBJ_MISSION_SATELLITE = 0x00008000,
    OBJ_FIGHTER           = 0x00010000,
    OBJ_FREIGHTER         = 0x00020000,
    OBJ_GUNBOAT           = 0x00040000,
    OBJ_CRUISER           = 0x00080000,
    OBJ_TRANSPORT         = 0x00100000,
    OBJ_CAPITAL           = 0x00200000,
    OBJ_MINING            = 0x00400000,
    OBJ_GUIDED            = 0x00800000,
    OBJ_BULLET            = 0x01000000,
    OBJ_MINE              = 0x02000000,
    OBJ_LOOT              = 0x04000000,
    OBJ_ASTEROID          = 0x08000000,

    // Convenience masks used by the object predicates.
    OBJ_PLANETARY_BODY = OBJ_MOON | OBJ_PLANET | OBJ_SUN,               // & 0x7
    OBJ_SYSTEM_GATE    = OBJ_JUMP_GATE | OBJ_AIRLOCK_GATE | OBJ_JUMP_HOLE // & 0xc40
};

namespace Archetype {
// Runtime class-type tag returned by each archetype's virtual get_class_type().
// Values are the constants each subclass returns (mov eax,IMM; ret); the enum
// only needs to exist for the ?AW4AClassType@Archetype@@ return-type mangling.
enum AClassType {
    ACLASS_COMMODITY       = 0x0a,
    ACLASS_SHIELD          = 0x0d,
    ACLASS_MINE_DROPPER    = 0x12,
    ACLASS_TRADELANE_EQUIP = 0x1d,
};
}

#endif // COMMON_DLL_COMMON_H
