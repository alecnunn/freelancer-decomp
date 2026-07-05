// CostumeDescriptions -- the loaded character-appearance database: sorted
// containers of costume / bodypart / accessory descriptions plus their name->id
// lookup tables (CharDescrip.cpp in the original). Recovered from Common.dll.
// Symbol-rich unit: real member functions mangle to the original symbols and
// objdiff pairs them automatically.
//
// This pass implements only the thin public accessors that forward to the
// (deferred) red-black-tree finders and return a single field of the found
// record:
//   find_costume_id     -> costume::m_id       (costume + 0x00)
//   get_costume_gender  -> costume::m_gender    (costume + 0x04)
//   find_part_id        -> bodypart::m_id       (bodypart + 0x00)
//   find_accessory_id   -> accessory::m_id      (accessory + 0x00)
// Each is the `p = find_*(...); return p ? p->field : 0;` idiom -- /O2 hoists
// the zero into a callee-saved register (push esi; xor esi,esi; ...; mov eax,esi)
// across the call, which the natural ternary reproduces.
//
// The finders themselves (find_costume/find_bodypart/find_accessory), the
// ctor/dtor (STL map/list construction), get_costume, the string-returning
// get_part_name/get_part_mesh and the INI loaders are deferred.
//
// costume is this container's own value type and is defined here (its sole
// definition). bodypart and accessory are defined in their own translation
// units (bodypart.cpp / accessory.cpp) within the unity build, so they are only
// forward-declared here and their leading id field is read through a pointer
// cast -- this compiles regardless of unity include order and emits the same
// `mov eax,[eax]` the original does, while avoiding any duplicate type
// definition (ODR clash) in the single TU.
#include "common.h"

// bodypart / accessory: full definitions live in their own .cpp; name only is
// needed here so the finder return types mangle to ...PBUbodypart@@ / PBUaccessory@@.
struct bodypart;
struct accessory;

// costume -- one costume description record (map node value). Only the two
// fields these accessors read are known/needed here.
struct costume {
    unsigned long m_id;      // +0x00  hashed costume id
    int           m_gender;  // +0x04
};

struct CostumeDescriptions {
    // Deferred finders (red-black-tree lookups); declared so the accessors below
    // can call them and mangle to the original callee symbols.
    const costume*   find_costume(const char* name) const;
    const costume*   find_costume(unsigned long id) const;
    const bodypart*  find_bodypart(int type, const char* name) const;
    const accessory* find_accessory(const char* name) const;

    // Implemented this pass.
    unsigned long find_costume_id(const char* name) const;
    int           get_costume_gender(unsigned long id) const;
    unsigned long find_part_id(int type, const char* name) const;
    unsigned long find_accessory_id(const char* name) const;
};

unsigned long CostumeDescriptions::find_costume_id(const char* name) const {
    const costume* c = find_costume(name);
    return c ? c->m_id : 0;
}

int CostumeDescriptions::get_costume_gender(unsigned long id) const {
    const costume* c = find_costume(id);
    return c ? c->m_gender : 0;
}

unsigned long CostumeDescriptions::find_part_id(int type, const char* name) const {
    const bodypart* b = find_bodypart(type, name);
    return b ? *reinterpret_cast<const unsigned long*>(b) : 0;
}

unsigned long CostumeDescriptions::find_accessory_id(const char* name) const {
    const accessory* a = find_accessory(name);
    return a ? *reinterpret_cast<const unsigned long*>(a) : 0;
}
