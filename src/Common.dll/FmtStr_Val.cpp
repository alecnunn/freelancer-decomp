// FmtStr::Val -- a single value node in a FmtStr's linked list of format
// arguments. Recovered from Common.dll; size 0x0c. Symbol-rich unit: real
// member functions mangle to the original symbols and pair automatically.
//
// The enclosing scope FmtStr is modeled as a namespace (as with Archetype::*):
// MSVC mangles a class nested in a class identically to one nested in a
// namespace, so `namespace FmtStr { struct Val }` reproduces the original
// `Val@FmtStr@@` qualified names.
//
// Layout (from ctor 0x630d570 / InitFromVoid 0x630d5a0 / flatten 0x630d460):
//   +0x00 m_next  Val* linked-list next node (0 for the tail)
//   +0x04 m_data  void* union payload: nested FmtStr* (type 0x21 '!'),
//                 allocated 0x14-byte blob (type 0x4e 'N'), or a raw pointer
//   +0x08 m_type  unsigned short discriminator ('!' / 'N' / other)
//   +0x0a m_flag  unsigned char
//
// Only the trivial constructors are matched here. InitFromVoid, flatten,
// get_flattened_size, operator==, the destructor and the compiler-generated
// copy ctor / copy assign allocate, recurse or loop and are deferred.
#include "common.h"

namespace FmtStr {

struct Val {
    Val*           m_next;   // +0x00
    void*          m_data;   // +0x04
    unsigned short m_type;   // +0x08
    unsigned char  m_flag;   // +0x0a
    unsigned char  _pad_b;   // +0x0b

    Val(const Val& o);
    Val(unsigned short g, void* p, unsigned char e);
    Val(const void* p);
    Val(const void* p, int& r);
    ~Val();

    Val& operator=(const Val& o);
    bool operator==(const Val& o) const;

    unsigned int flatten(void* dst, unsigned int cap) const;
    unsigned int get_flattened_size() const;

private:
    int InitFromVoid(const void* p);
};

// Val(unsigned short, void*, unsigned char) @ 0x630d570 -- direct field init.
Val::Val(unsigned short g, void* p, unsigned char e) {
    m_data = p;
    m_next = 0;
    m_type = g;
    m_flag = e;
}

// Val(const void*) @ 0x630d680 -- zero the link, then decode the blob.
Val::Val(const void* p) {
    m_next = 0;
    InitFromVoid(p);
}

// Val(const void*, int&) @ 0x630d660 -- as above, returning the byte count.
Val::Val(const void* p, int& r) {
    m_next = 0;
    r = InitFromVoid(p);
}

} // namespace FmtStr
