// CEquip -- base class of the mounted-equipment family (CEShield/CEEngine/
// CEGun/CELauncher/...). Shallow polymorphic class; fields from +0x08. The
// virtuals are declared in true vtable order (slot 0 = deleting dtor) so the
// self-dispatch methods (e.g. IsFunctioning) emit the right vtable offsets.
#include "common.h"
#include "archetype.h"

unsigned int Arch2Good(unsigned int arch);   // ?Arch2Good@@YAII@Z

struct CEquip {
    // vftable ptr at +0x00
    unsigned char  _pad_0x04[4];   // +0x04
    unsigned short m_id;           // +0x08  equipment id
    unsigned char  _pad_0x0a[2];   // +0x0a
    Archetype::Root* m_arch;       // +0x0c  archetype (equipment data)
    bool           m_active;       // +0x10
    bool           m_destroyed;    // +0x11
    bool           m_temporary;    // +0x12
    unsigned char  _pad_0x13;      // +0x13
    unsigned int   m_type;         // +0x14

    unsigned short GetID() const;
    unsigned int GetType() const;

    // --- virtuals, in vtable slot order ---
    virtual ~CEquip();                   // slot 0 (deleting dtor)
    virtual bool IsActive() const;       // slot 1  (byte 0x04)
    virtual bool IsDestroyed() const;    // slot 2  (byte 0x08)
    virtual bool IsFunctioning() const;  // slot 3  (byte 0x0c)
    virtual bool _is_disabled() const;   // slot 4  (byte 0x10)  folds DisableController
    virtual bool IsTemporary() const;    // slot 5
    virtual bool IsLootable() const;     // (body offset-based; slot not load-bearing here)
    virtual float GetMaxHitPoints() const;
};

unsigned short CEquip::GetID() const { return m_id; }
unsigned int CEquip::GetType() const { return m_type; }

CEquip::~CEquip() {}
bool CEquip::IsActive() const { return m_active; }
bool CEquip::IsDestroyed() const { return m_destroyed; }
bool CEquip::IsFunctioning() const {
    return IsActive() && !_is_disabled() && !IsDestroyed();
}
bool CEquip::_is_disabled() const { return false; }
bool CEquip::IsTemporary() const { return m_temporary; }
bool CEquip::IsLootable() const {
    if (m_arch->lootable != 0)
        return Arch2Good(m_arch->good_id) != 0;
    return false;
}
float CEquip::GetMaxHitPoints() const { return m_arch->hit_pts; }
