// Archetype::CollisionGroup -- a sub-object collision group on an equippable
// archetype (id, name, hit-point fractions, and three CollisionGroupDesc
// lists for child/damage/regen descriptions).
//
// Recovered from Common.dll; size 0x6c. Symbol-rich unit.
//
// This class exposes only four out-of-line symbols, ALL of which are
// compiler-generated and STL-heavy:
//   ??0CollisionGroup@Archetype@@QAE@XZ        default ctor
//   ??1CollisionGroup@Archetype@@QAE@XZ        dtor
//   ??0CollisionGroup@Archetype@@QAE@ABU01@@Z  copy ctor
//   ??4CollisionGroup@Archetype@@QAEAAU01@ABU01@@Z  copy assign
//
// The default ctor default-constructs a CacheString (calls CacheString::clear),
// two ID_String members (ID_String::clear), and THREE std::list members (each
// does operator new for a sentinel node), inside an SEH unwind frame; the dtor
// walks each list calling std::list<...>::erase in a loop. Byte-matching any of
// them requires the exact MSVC6 std::list / ID_String instantiations to live in
// common.h, and the copy ctor / copy assign only emit via STL container ODR-use.
// All four are therefore DEFERRED to a later pass that lands those types; this
// file records the byte-exact layout so that pass can drop in the natural C++.
#include "common.h"

struct CollisionGroup {              // Archetype::CollisionGroup, size 0x6c
    int            m_field00;        // +0x00  = 0
    unsigned short m_id;             // +0x04  = SUBOBJ_ID_NONE (sub-object id)
    unsigned char  _pad06[2];        // +0x06
    CacheString    m_name;           // +0x08  default-constructed (clear)
    int            m_field0c;        // +0x0c  = 1
    int            m_field10;        // +0x10  = 0
    bool           m_flag14;         // +0x14  = 0
    bool           m_flag15;         // +0x15  = 0
    bool           m_flag16;         // +0x16  = 0
    unsigned char  _pad17;           // +0x17
    int            m_field18;        // +0x18  = 0
    int            m_field1c;        // +0x1c  = 0
    float          m_float20;        // +0x20  = 1.0f
    bool           m_flag24;         // +0x24  = 0
    unsigned char  _pad25[3];        // +0x25
    int            m_field28;        // +0x28  = 0
    int            m_field2c;        // +0x2c  = 0
    int            m_field30;        // +0x30  = 0
    unsigned int   m_str34;          // +0x34  ID_String (clear)
    unsigned int   m_str38;          // +0x38  ID_String (clear)
    float          m_float3c;        // +0x3c  = 1.0f
    unsigned char  m_list40[12];     // +0x40  std::list<CollisionGroupDesc> (node 0x10)
    unsigned char  m_list4c[12];     // +0x4c  std::list<CollisionGroupDesc> (node 0x10)
    unsigned char  m_list58[12];     // +0x58  std::list<...>               (node 0x14, elem 0xc)
    int            m_field64;        // +0x64  = 0
    int            m_field68;        // +0x68  = 0
};

// No trivial getters/setters/operators exist for Archetype::CollisionGroup in
// the delinked target -- only the four compiler-generated symbols noted above,
// all deferred. Layout recovered for the follow-up STL pass.
