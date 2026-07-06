// CEquip -- base class of the mounted-equipment family (CEShield/CEEngine/
// CEGun/CELauncher/...). Shallow polymorphic class; fields from +0x08. The
// virtuals are declared in true vtable order (slot 0 = deleting dtor) so the
// self-dispatch methods (e.g. IsFunctioning) emit the right vtable offsets.
#include "common.h"
#include "archetype.h"

unsigned int Arch2Good(unsigned int arch);   // ?Arch2Good@@YAII@Z
extern "C" char _delink_ida_const_start[];  // delinked read-only const blob

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

    // --- virtuals, in true vtable slot order (slot N = byte 4*N). Slots not
    //     yet reconstructed are placeholders that only hold their position so
    //     the self-dispatch methods below emit the correct vtable offsets. ---
    virtual ~CEquip();                       // 0  deleting dtor
    virtual bool  IsActive() const;          // 1  (0x04)
    virtual bool  IsDestroyed() const;       // 2  (0x08)
    virtual bool  IsFunctioning() const;     // 3  (0x0c)
    virtual bool  _is_disabled() const;      // 4  (0x10)  folds DisableController
    virtual bool  IsTemporary() const;       // 5  (0x14)
    virtual void  _slot6();                  // 6  (0x18)  CanDelete
    virtual void  _slot7();                  // 7  (0x1c)
    virtual bool  IsLootable() const;        // 8  (0x20)
    virtual void  _slot9();                  // 9  (0x24)  Update
    virtual void  _slot10();                 // 10 (0x28)  GetEquipDesc
    virtual void  _slot11();                 // 11 (0x2c)  GetStatus
    virtual void  _slot12();                 // 12 (0x30)  Activate
    virtual void  _slot13();                 // 13 (0x34)  Destroy
    virtual float GetMaxHitPoints() const;   // 14 (0x38)
    virtual float GetHitPoints() const;      // 15 (0x3c)
    virtual void  _slot16();                 // 16 (0x40)
    virtual float GetRelativeHealth() const; // 17 (0x44)
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

// GetHitPoints' real body is a tail-call (jmp [vtable+0x38]) -- unmatchable;
// this placeholder body only holds vtable slot 15 for GetRelativeHealth.
float CEquip::GetHitPoints() const { return 0.0f; }

float CEquip::GetRelativeHealth() const {
    float max = GetMaxHitPoints();
    if (max != *(const float*)(_delink_ida_const_start + 0x54))
        return GetHitPoints() / max;
    return *(const float*)(_delink_ida_const_start + 0x54);
}

// Placeholder virtuals -- position-only (real methods deferred).
void CEquip::_slot6() {}
void CEquip::_slot7() {}
void CEquip::_slot9() {}
void CEquip::_slot10() {}
void CEquip::_slot11() {}
void CEquip::_slot12() {}
void CEquip::_slot13() {}
void CEquip::_slot16() {}
