// CEGun -- a mounted gun/launcher (CEquip<-...<-CAttachedEquip<-CEGun). Mostly
// targeting geometry; only the offset-based accessors are recovered here.
// Modeled flat; the leading pad accounts for the vptr + base fields.
#include "common.h"
#include "archetype.h"

struct CEGun {
    unsigned char        _pad_0x00[0x4c];   // +0x00 .. +0x4c  vptr + base fields
    Archetype::Munition* m_munition;        // +0x4c  loaded munition archetype
    unsigned char        _pad_0x50[0x1bc];  // +0x50 .. +0x20c
    bool                 m_azimuth_moving;   // +0x20c
    unsigned char        _pad_0x20d[0x1b];   // +0x20d .. +0x228
    bool                 m_elevation_moving; // +0x228

    bool is_guided() const;
    bool IsJointInMotion() const;
};

bool CEGun::is_guided() const { return m_munition->guidance != 0; }
bool CEGun::IsJointInMotion() const {
    return m_azimuth_moving && m_elevation_moving;
}
