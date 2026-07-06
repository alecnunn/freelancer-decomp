// CELauncher -- a projectile launcher (gun/missile) with N barrels
// (CEquip<-...<-CAttachedEquip<-CEGun<-CELauncher). Only the barrel-count
// accessor is recovered here. Modeled flat; the leading pad accounts for the
// vptr + base fields. Barrels are a fixed array at +0x54, stride 0x34, each
// terminated by an id of 0xffffffff.
#include "common.h"

struct CELauncher {
    struct Barrel { unsigned int id; unsigned char _pad_0x04[0x30]; };  // 0x34

    unsigned char _pad_0x00[0x54];   // +0x00 .. +0x54  vptr + base fields
    Barrel        m_barrels[8];      // +0x54  (sentinel-terminated)

    unsigned int GetProjectilesPerFire() const;
};

unsigned int CELauncher::GetProjectilesPerFire() const {
    int count = 0;
    if (m_barrels[0].id != 0xffffffff) {
        const Barrel* b = &m_barrels[0];
        do {
            ++b;
            ++count;
        } while (b->id != 0xffffffff);
    }
    return count;
}
