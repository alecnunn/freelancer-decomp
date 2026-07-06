// IObjInspectImpl -- base implementation of the IObjInspect read-only object
// interface. Recovered from Common.dll (symbol-rich unit). The single real data
// member is m_cobject (a CObject* at +0x10); nearly every method dispatches
// through it with an object-class flag check and a call into the concrete
// engine class (CShip/CEqObj/CSimple/...). Those dispatchers, plus the
// vtable-heavy ctor/dtor and the compiler-generated copy members, are deferred.
//
// This pass implements the handful of members that touch only m_cobject with no
// external call. They are declared `virtual` so MSVC mangles them with the
// original 'U' (public virtual) access code; the method bodies never reference
// the vtable(s), so modeling the exact multiple-inheritance vptr layout is
// unnecessary -- a single implicit vptr at +0 plus padding that places
// m_cobject at +0x10 reproduces the field access byte-for-byte.
#include "common.h"

class Vector;  // returned by reference only; incomplete type is sufficient

struct IObjInspectImpl {
    // implicit vptr at +0x00 (from the virtual members below)
    unsigned char pad_04[0x0c];  // +0x04 .. +0x0f (2nd vptr, Watchable, CBase vptr)
    void*         m_cobject;     // +0x10  the inspected CObject

    virtual const Vector& get_position() const;
    virtual long          get_index() const;
};

const Vector& IObjInspectImpl::get_position() const {
    return *(const Vector*)((const char*)m_cobject + 0x2c);
}

long IObjInspectImpl::get_index() const {
    return *(const long*)((const char*)m_cobject + 4);
}
