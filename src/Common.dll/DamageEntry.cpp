// DamageEntry -- one sub-object damage record (id, health, fate).
// Recovered from Common.dll; size 0x0C. Symbol-rich unit: real member
// functions mangle to the original symbols and pair automatically.
#include "common.h"
#include <list>

struct DamageEntry {
    enum SubObjFate {
        FATE_BUILT       = 0,
        FATE_DESTROY_ROOT,
        FATE_DAMAGE,
        FATE_DESTROY,
    };

    unsigned short m_subobj_id;  // +0x00  sub-object id (SUBOBJ_ID_NONE sentinel)
    unsigned char  _pad2[2];     // +0x02
    float          m_health;     // +0x04  health (default -1.0)
    SubObjFate     m_fate;       // +0x08

    DamageEntry();

    bool operator==(const DamageEntry& o) const;
    bool operator!=(const DamageEntry& o) const;
    bool operator<(const DamageEntry& o) const;
    bool operator>(const DamageEntry& o) const;
};

DamageEntry::DamageEntry() {
    m_subobj_id = SUBOBJ_ID_NONE;
    m_health = -1.0f;
    m_fate = FATE_BUILT;
}

bool DamageEntry::operator==(const DamageEntry& o) const {
    return o.m_subobj_id == m_subobj_id && o.m_health == m_health && o.m_fate == m_fate;
}

bool DamageEntry::operator!=(const DamageEntry& o) const {
    bool eq = m_subobj_id == o.m_subobj_id && m_health == o.m_health && m_fate == o.m_fate;
    return !eq;
}

bool DamageEntry::operator<(const DamageEntry& o) const {
    return o.m_subobj_id < m_subobj_id;
}

bool DamageEntry::operator>(const DamageEntry& o) const {
    return o.m_subobj_id > m_subobj_id;
}

// STL container the original instantiates over DamageEntry.
template class std::list<DamageEntry>;
