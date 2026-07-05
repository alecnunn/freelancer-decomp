// CollisionGroupDesc -- a collision-group / sub-object health entry
// (sub-object id + health fraction). Recovered from Common.dll; size 0x08.
// Symbol-rich unit: real member functions mangle to the original symbols and
// pair automatically. Ordering is by m_id (see CArchGroup::GetCollisionGroupDesc,
// which fills m_id from the arch sub-object id and m_health from hit_pts/max).
#include "common.h"
#include <list>

struct CollisionGroupDesc {
    unsigned short m_id;      // +0x00  sub-object id
    unsigned char  _pad2[2];  // +0x02
    float          m_health;  // +0x04  health fraction

    bool operator==(const CollisionGroupDesc& o) const;
    bool operator!=(const CollisionGroupDesc& o) const;
    bool operator<(const CollisionGroupDesc& o) const;
    bool operator>(const CollisionGroupDesc& o) const;
};

// Favor-size idiom in the original (see EquipDesc operators); scope to /Os.
#pragma optimize("s", on)
bool CollisionGroupDesc::operator==(const CollisionGroupDesc& o) const { return m_id == o.m_id; }
bool CollisionGroupDesc::operator!=(const CollisionGroupDesc& o) const { return m_id != o.m_id; }
bool CollisionGroupDesc::operator<(const CollisionGroupDesc& o) const { return m_id < o.m_id; }
bool CollisionGroupDesc::operator>(const CollisionGroupDesc& o) const { return m_id > o.m_id; }
#pragma optimize("", on)

// STL container the original instantiates over CollisionGroupDesc.
template class std::list<CollisionGroupDesc>;
