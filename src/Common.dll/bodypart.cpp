// bodypart -- one costume body-part description (a hashed id + a name string +
// a detail/LOD index and two back-pointers). Recovered from Common.dll; size
// 0x20. Symbol-rich unit: real member functions mangle to the original symbols
// and objdiff pairs them automatically.
//
// Layout (from the ctor/dtor/init codegen):
//   +0x00  unsigned int  m_id       hashed id (atol()/CreateID() of the name)
//   +0x04  std::string   m_name     embedded Dinkumware ref-counted (COW) string
//                                      +0x04 allocator byte, +0x08 _Ptr,
//                                      +0x0c _Len, +0x10 _Res
//   +0x14  int           m_index    LOD / detail index (init's 3rd arg)
//   +0x18  void*         m_switch   DetailSwitchTable*  (init's last arg)
//   +0x1c  void*         m_list     std::list<std::string>* (init's 4th arg)
//
// The original build has no <string> header available in the decomp include
// tree, so the embedded COW string is modelled here by a byte-exact local
// helper (bp_string). It carries a UNIQUE name so it can never ODR-clash with
// another TU in the unity build; it is intentionally NOT placed in common.h.
// bodypart's ctor/dtor mangling does not depend on the member's type, so the
// original symbols are still produced.
//
// The default ctor inlines the string's default ctor (empty-allocator copy ->
// the `mov cl,[esp+3]` byte read, then _Ptr/_Len/_Res zeroed) and the dtor
// inlines the string's _Tidy(true) (ref-count decrement, else deallocate).
// The deallocate path in the original calls an internal static free-thunk
// (sub_6391D5A); the semantically-correct ::operator delete is emitted here,
// which differs only in that one call's relocation target.
#include "common.h"

// --- embedded ref-counted string model (file-local, uniquely named) ---------
struct bp_alloc {};   // empty allocator; occupies 1 byte in MSVC

struct bp_string {
    bp_alloc     _Al;    // +0x00  allocator subobject (empty)
    char*        _Ptr;   // +0x04  buffer (points past the 1-byte ref count)
    unsigned int _Len;   // +0x08  length
    unsigned int _Res;   // +0x0c  reserved

    bp_string(bp_alloc _A = bp_alloc()) : _Al(_A) {
        _Ptr = 0;
        _Len = 0;
        _Res = 0;
    }
    // Defined inline so /O2 inlines the ref-count-decrement/deallocate body
    // directly into bodypart::~bodypart (the original inlines the string's
    // _Tidy(true) rather than emitting a tail call to a separate dtor).
    ~bp_string() {
        if (_Ptr != 0) {
            char c = _Ptr[-1];
            char* _R = _Ptr - 1;
            if (c == 0 || c == (char)0xff)
                ::operator delete(_R);
            else
                *_R = (char)(c - 1);
        }
        _Ptr = 0;
        _Len = 0;
        _Res = 0;
    }
};

// --- bodypart ---------------------------------------------------------------
struct bodypart {
    unsigned int m_id;      // +0x00
    bp_string    m_name;    // +0x04  (size 0x10)
    int          m_index;   // +0x14
    void*        m_switch;  // +0x18  DetailSwitchTable*
    void*        m_list;    // +0x1c  std::list<std::string>*

    bodypart();
    ~bodypart();
};

bodypart::bodypart() {
    // m_name is default-constructed by the member initializer (emitted first).
    m_id = 0;
    m_index = 0;
    m_switch = 0;
    m_list = 0;
}

bodypart::~bodypart() {
    // m_name's destructor (inlined _Tidy) is emitted here automatically.
}
