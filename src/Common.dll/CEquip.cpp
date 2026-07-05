// CEquip -- base class of the mounted-equipment family (CEShield/CEEngine/
// CEGun/CELauncher/...). Shallow polymorphic class (own vtable ~18 slots);
// fields from +0x08. Modeled flat with a leading vptr word.
#include "common.h"

namespace Archetype { struct Equipment; }

struct CEquip {
    // vftable ptr at +0x00
    unsigned char  _pad_0x04[4];   // +0x04
    unsigned short m_id;           // +0x08  equipment id
    unsigned char  _pad_0x0a[2];   // +0x0a
    Archetype::Equipment* m_arch;  // +0x0c  archetype (max hit pts at +0x1c)
    bool           m_active;       // +0x10
    bool           m_destroyed;    // +0x11
    bool           m_temporary;    // +0x12
    unsigned char  _pad_0x13;      // +0x13
    unsigned int   m_type;         // +0x14

    unsigned short GetID() const;
    unsigned int GetType() const;
    virtual bool IsActive() const;
    virtual bool IsDestroyed() const;
    virtual bool IsTemporary() const;
    virtual float GetMaxHitPoints() const;
};

unsigned short CEquip::GetID() const { return m_id; }
unsigned int CEquip::GetType() const { return m_type; }
bool CEquip::IsActive() const { return m_active; }
bool CEquip::IsDestroyed() const { return m_destroyed; }
bool CEquip::IsTemporary() const { return m_temporary; }
float CEquip::GetMaxHitPoints() const { return *(const float*)((const char*)m_arch + 0x1c); }
