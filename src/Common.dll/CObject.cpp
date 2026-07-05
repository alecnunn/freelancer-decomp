// CObject -- the mid-level base of the simulatable-object hierarchy
// (EngineObject -> CObject -> CSimple -> CEqObj/CShip/CSolar/...). Recovered
// from Common.dll. Modeled flat here (owns 0x00..0xa0: the EngineObject base
// region plus CObject's own fields); CSimple derives from it. Only offsets
// touched by matched methods are named.
#include "EngineObject.h"

namespace Archetype { struct Root; }
struct IObjDB;

// One entry of CObject's part<->instance map (size 0x0c).
struct CObjPart {
    unsigned int part_id;   // +0x00
    long         inst_id;   // +0x04
    bool         shield;    // +0x08
    unsigned char _pad9[3]; // +0x09
};

struct CObject : EngineObject {
    // EngineObject owns 0x00..0x4c (vftable ptr, m_instance_id@0x04, transform,
    // m_position@0x2c, radius, ...). CObject's own fields begin at +0x4c.
    unsigned char _pad_0x4c[8];      // +0x4c .. +0x54
    void*         m_phys;            // +0x54  physics controller (0 = static)
    unsigned char _pad_0x58[4];      // +0x58
    unsigned int  m_part_count;      // +0x5c  0 = no sub-parts
    unsigned char _pad_0x60[8];      // +0x60
    CObjPart*     m_part_begin;      // +0x68  part-map vector begin
    CObjPart*     m_part_end;        // +0x6c  part-map vector end
    unsigned char _pad_0x70[0x18];   // +0x70
    Archetype::Root* m_arch;         // +0x88  archetype root
    unsigned char _pad_0x8c[0xc];    // +0x8c
    unsigned int  m_ref_count;       // +0x98
    unsigned char _pad_0x9c[4];      // +0x9c  (size rounds to 0xa0)

    unsigned int AddRef();
    long part_to_inst(unsigned int part) const;
    unsigned int inst_to_part(long inst) const;
    bool is_shield_part(unsigned int part) const;
    virtual float get_mass() const;
    virtual Vector get_center_of_mass() const;
    Vector get_moment_of_inertia() const;

    // Declared so derived classes' base-qualified calls resolve (defined elsewhere).
    virtual void open(Archetype::Root* arch);
};

// PhySys free functions used by the physics accessors (defined in another unit;
// with no link the undefined externals are harmless -- only the reloc name matters).
namespace PhySys {
    float  GetMass(const CObject* obj);
    Vector GetCenterOfMass(const CObject* obj);
    Vector GetMomentOfInertia(const CObject* obj);
}

unsigned int CObject::AddRef() { return ++m_ref_count; }

long CObject::part_to_inst(unsigned int part) const {
    if (m_part_count == 0)
        return m_instance_id;
    for (const CObjPart* i = m_part_begin; i != m_part_end; ++i)
        if (i->part_id == part)
            return i->inst_id;
    return -1;
}

unsigned int CObject::inst_to_part(long inst) const {
    for (const CObjPart* i = m_part_begin; i != m_part_end; ++i)
        if (i->inst_id == inst)
            return i->part_id;
    return 0;
}

bool CObject::is_shield_part(unsigned int part) const {
    for (const CObjPart* i = m_part_begin; i != m_part_end; ++i)
        if (i->part_id == part)
            return i->shield;
    return false;
}

float CObject::get_mass() const {
    if (m_phys != 0)
        return PhySys::GetMass(this);
    return *(const float*)((const char*)m_arch + 0x20);
}

Vector CObject::get_center_of_mass() const {
    if (m_phys != 0)
        return PhySys::GetCenterOfMass(this);
    return m_position;
}

Vector CObject::get_moment_of_inertia() const {
    if (m_phys != 0)
        return PhySys::GetMomentOfInertia(this);
    Vector v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    return v;
}
