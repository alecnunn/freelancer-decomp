// CEquipManager -- owns a ship/solar's mounted equipment as two
// std::list<CEquip*> (one general, one for attached/external equip) plus a
// decaying-cargo counter. Layout recovered from the ctor (two sentinel nodes
// allocated at 0xc bytes each).
#include "common.h"

class CEquip;

// MSVC6 Dinkumware std::list<CEquip*> -- an empty allocator (EBO), the circular
// sentinel node pointer, and the cached element count. Size 0xc.
struct EquipPtrList {
    unsigned char _alloc;      // +0x00  allocator (empty)
    unsigned char _pad[3];     // +0x01
    void*         _head;       // +0x04  sentinel node (next/prev)
    int           _size;       // +0x08
    int size() const { return _size; }
};

struct CEquipManager {
    int          m_field_0;    // +0x00
    EquipPtrList m_equip;      // +0x04  std::list<CEquip*>
    EquipPtrList m_attached;   // +0x10  std::list<CEquip*>
    int          m_decaying_cargo_count; // +0x1c

    int  Size() const;
    bool HasDecayingCargo() const;
};

int  CEquipManager::Size() const { return m_attached.size() + m_equip.size(); }
bool CEquipManager::HasDecayingCargo() const { return m_decaying_cargo_count > 0; }
