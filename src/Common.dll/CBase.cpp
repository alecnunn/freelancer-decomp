// CBase -- polymorphic base with a back-link pointer to an indexed owner.
// Recovered from Common.dll; size 0x08 (vfptr + one pointer). Symbol-rich
// unit: real member functions mangle to the original symbols and pair
// automatically. The virtual destructor makes MSVC synthesize the vfptr at
// +0x00, so m_link (declared first) lands at +0x04.
#include "common.h"

struct CBase {
    void* m_link;   // +0x04  pointer to owner; owner's +0x04 is a long index

    CBase();
    CBase(const CBase& o);
    virtual ~CBase();

    long get_index() const;
};

CBase::CBase() : m_link(0) {
}

CBase::CBase(const CBase& o) : m_link(o.m_link) {
}

CBase::~CBase() {
}

long CBase::get_index() const {
    return *(long*)((char*)m_link + 4);
}
