// CObject -- the mid-level base of the simulatable-object hierarchy
// (EngineObject -> CObject -> CSimple -> CEqObj/CShip/CSolar/...). Recovered
// from Common.dll. Modeled flat here (owns 0x00..0xa0: the EngineObject base
// region plus CObject's own fields); CSimple derives from it. Only offsets
// touched by matched methods are named.
#include "common.h"

namespace Archetype { struct Root; }
struct IObjDB;

// One entry of CObject's part<->instance map (size 0x0c).
struct CObjPart {
    unsigned int part_id;   // +0x00
    long         inst_id;   // +0x04
    bool         shield;    // +0x08
    unsigned char _pad9[3]; // +0x09
};

struct CObject {
    // implicit vftable pointer at +0x00
    unsigned int  m_inst_id;         // +0x04  instance id (returned when no parts)
    unsigned char _pad_0x08[0x4c];   // +0x08 .. +0x54  (EngineObject base)
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

    // Declared so derived classes' base-qualified calls resolve (defined elsewhere).
    virtual void open(Archetype::Root* arch);
};

unsigned int CObject::AddRef() { return ++m_ref_count; }

long CObject::part_to_inst(unsigned int part) const {
    if (m_part_count == 0)
        return m_inst_id;
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
