// GoodInfo -- a single "good" (tradeable/equippable archetype) descriptor.
// Recovered from Common.dll; size 0xc0. Symbol-rich unit: real member
// functions mangle to the original symbols and pair automatically.
//
// Layout (from the ctor/dtor/copy-ctor): a CommReferrable base at +0x00
// (vftable ptr, then two small fields), an ID_String at +0x48, five
// CacheString handles at +0x74..+0x84, scalar fields, three
// std::list<EquipDesc> members at +0x94/+0xa0/+0xac, and two trailing
// dwords at +0xb8/+0xbc. Only the visual/attachment CacheString at +0x84 is
// load-bearing for the method implemented here, so the rest is padded to keep
// the total size (0xc0) exact without pulling in the base class / ID_String /
// STL types (they belong to the ctor/dtor which are deferred below).
#include "common.h"

struct GoodInfo {
    unsigned char pad_0x00[0x84]; // CommReferrable base, ID_String, other CacheStrings, scalars
    CacheString   m_visual;       // +0x84  visual/hardpoint attachment string handle
    unsigned char pad_0x88[0x38]; // scalars + three std::list<EquipDesc> + trailing dwords (through 0xc0)

    bool has_visual_attachment() const;
};

// ?has_visual_attachment@GoodInfo@@QBE_NXZ
// The CacheString id at +0x84 is used as a char pointer; the good has a visual
// attachment iff that string is non-empty (first byte != 0).
// NOTE: caps at 66.29%. The original materializes the bool via a branch
// (mov dl,[ecx]; xor al,al; test dl,dl; je; mov al,1) with the pointer kept in
// ecx; MSVC6 here emits the /O2 setne idiom into eax instead. Neither
// optimize("s") nor the if/return or char-return forms reproduce the branch +
// ecx scheduling -- the same orthogonal register-scheduling cap noted for the
// comparison operators. Left as the cleanest expression.
bool GoodInfo::has_visual_attachment() const {
    return *reinterpret_cast<const char*>(m_visual.id) != 0;
}

// Deferred (not byte-matchable in isolation this pass):
//   ??0GoodInfo@@QAE@XZ        default ctor -- constructs CommReferrable base,
//                              ID_String, five CacheStrings and three
//                              std::list<EquipDesc> members via operator new;
//                              needs the exact base/member types + STL codegen.
//   ??1GoodInfo@@QAE@XZ        dtor -- std::list<EquipDesc>::erase loops + SEH.
//   ??0GoodInfo@@QAE@ABU0@@Z   copy-ctor  (STL-driven, emitted via container use).
//   ??4GoodInfo@@QAEAAU0@ABU0@@Z copy-assign (same).
