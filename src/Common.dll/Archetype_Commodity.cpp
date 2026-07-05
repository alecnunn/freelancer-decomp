// Archetype::Commodity -- a tradeable cargo archetype (class type 10).
// Recovered from Common.dll. Single-inheritance chain
// Commodity : Equipment : Root; the base subobject occupies 0x00..0x5c and
// Commodity's own fields begin at 0x5c. Total instance size 0x7c.
//
// Symbol-rich unit: these real member definitions mangle to the original
// symbols and objdiff pairs them automatically (no claim needed).
//
// Deferred (see notes): the ICliObj* constructor (SEH + Root/ID_String calls),
// the compiler-synthesized copy-ctor / default-ctor-closure, and read()
// (INI parsing, ArchDB lookups). operator= is not present in the target.
#include "common.h"

namespace Archetype {

struct Equipment;   // base class / loot appearance pointee
struct CargoPod;    // pod appearance pointee
struct ICliObj;     // construction argument

struct Commodity {
    // vptr implicitly at 0x00 (from the virtual functions below)
    unsigned char _pad_0x04[0x18];      // 0x04..0x1c  Root base fields
    float         m_hit_pts;            // 0x1c  base health scale (ctor: 1.0f)
    unsigned char _pad_0x20[0x50];      // 0x20..0x70  base + Equipment fields
    float         m_decay_per_second;   // 0x70
    Equipment*    m_loot_appearance;    // 0x74
    CargoPod*     m_pod_appearance;     // 0x78
    // size 0x7c

    virtual AClassType get_class_type() const;
    virtual Equipment* get_loot_appearance();
    virtual CargoPod*  get_pod_appearance();
    float get_decay_per_second() const;
};

AClassType Commodity::get_class_type() const {
    return (AClassType)0xa;
}

Equipment* Commodity::get_loot_appearance() {
    return m_loot_appearance ? m_loot_appearance : (Equipment*)this;
}

CargoPod* Commodity::get_pod_appearance() {
    return m_pod_appearance;
}

float Commodity::get_decay_per_second() const {
    float limit = m_hit_pts * 0.25f;
    return m_decay_per_second < limit ? m_decay_per_second : limit;
}

} // namespace Archetype
