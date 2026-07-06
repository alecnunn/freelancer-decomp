// CECargo -- a cargo/commodity equipment item (CEquip<-...<-CECargo). Only the
// offset-based accessor is recovered here. Modeled flat; the leading pad
// accounts for the vptr + base fields.
#include "common.h"

struct CECargo {
    unsigned char _pad_0x00[0x28];   // +0x00 .. +0x28  vptr + base fields
    unsigned int  m_count;           // +0x28

    unsigned int GetCount() const;
};

unsigned int CECargo::GetCount() const { return m_count; }
