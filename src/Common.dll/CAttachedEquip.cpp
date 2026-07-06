// CAttachedEquip -- intermediate equipment class (CEquip<-CExternalEquip<-
// CAttachedEquip<-CEShield/CEGun/...). Mostly vtable-dispatch logic; only the
// offset-based accessors are recovered here. Modeled flat (inherited
// CEquip::m_arch@0x0c); the leading pad accounts for the vptr + base fields.
#include "common.h"
#include "archetype.h"

struct CAttachedEquip {
    // vftable ptr @ +0x00 (from the virtuals below)
    unsigned char         _pad_0x04[8];    // +0x04 .. +0x0c
    Archetype::Equipment* m_arch;          // +0x0c  inherited CEquip archetype
    unsigned char         _pad_0x10[0x20]; // +0x10 .. +0x30
    float                 m_hit_pts;       // +0x30

    virtual int   GetToughness() const;
    virtual float GetHitPoints() const;
};

int   CAttachedEquip::GetToughness() const { return m_arch->toughness; }
float CAttachedEquip::GetHitPoints() const { return m_hit_pts; }
