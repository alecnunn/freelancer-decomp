// EquipDesc -- a single equipment/cargo entry (id, hardpoint, status, ...).
// Recovered from Common.dll; size 0x20. Symbol-rich unit: real member
// functions mangle to the original symbols and pair automatically.
#include "common.h"

struct EquipDesc {
    unsigned char  m_byte0;      // +0x00
    unsigned char  _pad1;        // +0x01
    unsigned short m_id;         // +0x02  equipment archetype id
    unsigned int   m_arch;       // +0x04  arch handle (-> Archetype::GetEquipment)
    CacheString    m_hardpoint;  // +0x08  mount point (CARGO_BAY_HP_NAME == internal)
    bool           m_equipped;   // +0x0c
    unsigned char  _pad_d[3];    // +0x0d
    float          m_status;     // +0x10  health fraction [0,1]
    int            m_count;      // +0x14  quantity
    bool           m_temporary;  // +0x18
    unsigned char  _pad_19[3];   // +0x19
    int            m_owner;      // +0x1c

    EquipDesc();

    unsigned short get_id() const;
    void set_id(unsigned short id);
    float get_status() const;
    void set_status(float status);
    bool is_equipped() const;
    void set_equipped(bool equipped);
    bool get_temporary() const;
    void set_temporary(bool temporary);
    void set_owner(int owner);
    const CacheString& get_hardpoint() const;
    void set_hardpoint(const CacheString& hp);
    bool is_internal() const;
    void make_internal();

    bool operator==(const EquipDesc& o) const;
    bool operator!=(const EquipDesc& o) const;
    bool operator<(const EquipDesc& o) const;
    bool operator>(const EquipDesc& o) const;

    static const CacheString CARGO_BAY_HP_NAME;
};

EquipDesc::EquipDesc() {
    m_byte0 = 0;
    m_id = SUBOBJ_ID_NONE;
    m_arch = 0;
    m_hardpoint = CARGO_BAY_HP_NAME;
    m_equipped = 0;
    m_status = 1.0f;
    m_count = 1;
    m_temporary = 0;
    m_owner = 0;
}

unsigned short EquipDesc::get_id() const { return m_id; }
void EquipDesc::set_id(unsigned short id) { m_id = id; }
float EquipDesc::get_status() const { return m_status; }
void EquipDesc::set_status(float status) { m_status = status; }
bool EquipDesc::is_equipped() const { return m_equipped; }
void EquipDesc::set_equipped(bool equipped) { m_equipped = equipped; }
bool EquipDesc::get_temporary() const { return m_temporary; }
void EquipDesc::set_temporary(bool temporary) { m_temporary = temporary; }
void EquipDesc::set_owner(int owner) { m_owner = owner; }
const CacheString& EquipDesc::get_hardpoint() const { return m_hardpoint; }
void EquipDesc::set_hardpoint(const CacheString& hp) { m_hardpoint = hp; }
bool EquipDesc::is_internal() const { return m_hardpoint.id == CARGO_BAY_HP_NAME.id; }
void EquipDesc::make_internal() { m_hardpoint = CARGO_BAY_HP_NAME; }

bool EquipDesc::operator==(const EquipDesc& o) const { return m_id == o.m_id; }
bool EquipDesc::operator!=(const EquipDesc& o) const { return m_id != o.m_id; }
bool EquipDesc::operator<(const EquipDesc& o) const { return m_id < o.m_id; }
bool EquipDesc::operator>(const EquipDesc& o) const { return m_id > o.m_id; }

// NOTE: the original also has standalone copy-ctor (??0EquipDesc@@QAE@ABU0@@Z)
// and copy-assign (??4EquipDesc@@QAEAAU0@ABU0@@Z) symbols. Those are the
// compiler-generated members, emitted out-of-line only because the STL
// container instantiations (std::vector/list<EquipDesc>) ODR-use them. They
// will fall out when those containers are implemented; matching them in
// isolation is not possible since MSVC inlines the trivial copy here.
