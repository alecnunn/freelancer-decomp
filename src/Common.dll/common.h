// Common.dll -- shared type declarations recovered from the original binary.
//
// These types are referenced across many translation units in the unity build.
// Keep layouts byte-exact: field offsets are load-bearing for matching.
#ifndef COMMON_DLL_COMMON_H
#define COMMON_DLL_COMMON_H

// A hashed string handle. Freelancer stores strings as a single 32-bit id.
// Size 4; assigned/compared as a plain dword by the original codegen.
struct CacheString {
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
