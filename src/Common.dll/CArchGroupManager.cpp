// CArchGroupManager -- owns the collision-group (destructible sub-object)
// hierarchy for a CEqObj. Only the trivial owner-init accessor is recovered
// here; Clear/Traverse walk the internal group list+map and are deferred.
#include "common.h"

struct CEqObj;

struct CArchGroupManager {
    CEqObj* m_owner;   // +0x00  owning object (set once)

    bool Init(CEqObj* obj);
};

// One-time owner binding: only takes effect while unset.
bool CArchGroupManager::Init(CEqObj* obj) {
    if (m_owner == 0)
        m_owner = obj;
    return m_owner != 0;
}
