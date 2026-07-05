// accessory -- one costume "accessory" description: a hashed id, three name
// strings (mesh, accessory-hardpoint, character-hardpoint) and an owned list of
// strings. Recovered from Common.dll; size 0x40. Symbol-rich unit: real member
// functions mangle to the original symbols and objdiff pairs them automatically.
//
// Layout (from the ctor/dtor/getter codegen):
//   +0x00  unsigned int              m_id          hashed id (_ultoa'd by get_name)
//   +0x04  std::string               m_mesh        Dinkumware ref-counted (COW) string
//   +0x14  std::string               m_accessory_hardpoint
//   +0x24  std::string               m_character_hardpoint
//   +0x34  std::list<std::string>    m_targets     embedded owned list (0x0c bytes)
//
// Each embedded string is +0x00 allocator byte, +0x04 _Ptr, +0x08 _Len,
// +0x0c _Res. Each getter is the inlined std::string::c_str() (return _Ptr, or
// the shared empty-string sentinel _Nullstr() when _Ptr is null).
//
// The original decomp include tree has no <string>/<list> headers, so the
// embedded Dinkumware string and list are modelled here by byte-exact,
// UNIQUELY-named file-local helpers (ac_string / ac_list). They can never
// ODR-clash with another TU in the unity build and are intentionally NOT placed
// in common.h. accessory's ctor/dtor/getter mangling does not depend on the
// member types, so the original symbols are still produced.
//
// The default ctor inlines each string's default ctor (empty-allocator copy ->
// the `mov ?l,[esp+?]` byte reads, then _Ptr/_Len/_Res zeroed) and the list's
// default ctor (operator new(0x18) sentinel node whose next/prev point to
// itself, _Size = 0), then sets m_id = 0 in the body.
//
// The dtor's leading list-clear loop and sentinel free call the original's
// internal std::list helpers (sub_62B9D50 / sub_6391D5A); the semantically
// equivalent inline erase + ::operator delete emitted here differ in those
// relocation targets. The three trailing string dtors (inlined _Tidy(true)
// ref-count decrement, else free) match byte-for-byte.
#include "common.h"

// --- embedded ref-counted string model (file-local, uniquely named) ---------
struct ac_alloc {};   // empty allocator; occupies 1 byte in MSVC

struct ac_string {
    ac_alloc     _Al;    // +0x00  allocator subobject (empty)
    char*        _Ptr;   // +0x04  buffer (points past the 1-byte ref count)
    unsigned int _Len;   // +0x08  length
    unsigned int _Res;   // +0x0c  reserved

    ac_string(ac_alloc _A = ac_alloc()) : _Al(_A) {
        _Ptr = 0;
        _Len = 0;
        _Res = 0;
    }
    ~ac_string();

    static const char* _Nullstr() { static const char _C = 0; return &_C; }
    const char* c_str() const { return _Ptr != 0 ? _Ptr : _Nullstr(); }
};

ac_string::~ac_string() {
    if (_Ptr != 0) {
        char* _R = _Ptr - 1;
        char c = *_R;
        if (c == 0 || c == (char)0xff)
            ::operator delete(_R);
        else
            *_R = (char)(c - 1);
    }
    _Ptr = 0;
    _Len = 0;
    _Res = 0;
}

// --- embedded owned list-of-strings model (file-local, uniquely named) -------
struct ac_node {
    ac_node*  _Next;   // +0x00
    ac_node*  _Prev;   // +0x04
    ac_string _Value;  // +0x08  (node size 0x18)
};

struct ac_list {
    ac_alloc     _Al;    // +0x00  allocator subobject (empty)
    ac_node*     _Head;  // +0x04  sentinel node
    unsigned int _Size;  // +0x08

    ac_list(ac_alloc _A = ac_alloc()) : _Al(_A) {
        _Head = (ac_node*)::operator new(sizeof(ac_node));
        _Head->_Next = _Head;
        _Head->_Prev = _Head;
        _Size = 0;
    }
    ~ac_list();
};

ac_list::~ac_list() {
    ac_node* _P = _Head->_Next;
    while (_P != _Head) {
        ac_node* _N = _P->_Next;
        _P->_Value.~ac_string();
        ::operator delete(_P);
        _P = _N;
    }
    ::operator delete(_Head);
    _Head = 0;
    _Size = 0;
}

// --- accessory --------------------------------------------------------------
struct accessory {
    unsigned int m_id;                    // +0x00
    ac_string    m_mesh;                  // +0x04
    ac_string    m_accessory_hardpoint;   // +0x14
    ac_string    m_character_hardpoint;   // +0x24
    ac_list      m_targets;               // +0x34

    accessory();
    ~accessory();

    const char* get_mesh() const;
    const char* get_accessory_hardpoint() const;
    const char* get_character_hardpoint() const;
};

accessory::accessory() {
    // m_mesh / m_accessory_hardpoint / m_character_hardpoint / m_targets are
    // default-constructed by their member initializers (emitted first); the
    // body only zeroes the id.
    m_id = 0;
}

accessory::~accessory() {
    // The members' destructors (list clear + three inlined string _Tidy) are
    // emitted here automatically, in reverse declaration order.
}

const char* accessory::get_mesh() const { return m_mesh.c_str(); }
const char* accessory::get_accessory_hardpoint() const { return m_accessory_hardpoint.c_str(); }
const char* accessory::get_character_hardpoint() const { return m_character_hardpoint.c_str(); }
