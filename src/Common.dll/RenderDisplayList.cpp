// RenderDisplayList -- an ordered list of polymorphic rich-text render
// elements (styles, glyph runs, images, ...) produced by the RDL readers and
// walked by TextRenderContext during layout/draw.
// Recovered from Common.dll; size 0x0C. Symbol-rich unit: real member
// functions mangle to the original symbols and pair automatically.
//
// The class is a thin wrapper around std::list<RDLElement*> (head pointer at
// +0x04, size at +0x08; node size 0x0C = {next, prev, elem}). As with the
// other STL-bearing classes in this unit (see DamageList / Archetype_Collision-
// Group), the list is modeled as a raw 8-byte blob so any POD neighbours land
// at the right offsets. Every RenderDisplayList method touches the list -- the
// default ctor (sentinel-node construction), the compiler-generated copy-ctor /
// copy-assign (deep clone via the element virtual clone at vtbl+0x1c), the
// dtor (node teardown), execute / update / get_element_count / get_dimensions /
// get_element_pos (all iterate the list and dispatch element virtuals) -- so
// every one is deferred: matching them requires the exact MSVC6
// std::list<RDLElement*> instantiation and the RDLElement vtable. The lone
// non-list member is a bool at +0x00 with no accessor of its own, so there is
// no pure-POD method to implement in isolation here.
#include "common.h"

struct RenderDisplayList {
    bool          m_field0;        // +0x00  (set in ctor; no accessor)
    unsigned char _pad_1[3];       // +0x01
    unsigned char m_elements[8];   // +0x04  std::list<RDLElement*> (head + size)
};
