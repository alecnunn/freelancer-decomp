// CECargo -- a cargo/commodity equipment item (CEquip<-...<-CECargo). Only the
// offset-based accessor is recovered here. Modeled flat; the leading pad
// accounts for the vptr + base fields.
#include "common.h"

struct CECargo {
    // vftable ptr @ +0x00 (from the virtual below)
    unsigned char _pad_0x04[0x20];   // +0x04 .. +0x24  base fields
    float         m_hit_pts;         // +0x24
    unsigned int  m_count;           // +0x28

    virtual void SetHitPoints(float hp);
    unsigned int GetCount() const;
};

void CECargo::SetHitPoints(float hp) { m_hit_pts = hp; }
unsigned int CECargo::GetCount() const { return m_count; }
