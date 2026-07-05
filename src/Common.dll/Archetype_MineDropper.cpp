// Archetype::MineDropper -- equipment archetype describing a mine launcher.
// Recovered from Common.dll. Symbol-rich unit: a real (virtual) member
// function mangles to the original symbol and pairs automatically.
//
// Layout note (from the ctor at 0x62f6b10): MineDropper derives through the
// chain Archetype::Root -> Equipment -> AttachedEquipment -> MineDropper and
// spans up to +0xA0. The substantive constructors (main ctor, copy ctor) and
// the compiler-generated default-constructor closure call into those base
// classes / embedded ID_String / CacheString members and are deferred; only
// the trivial virtual get_class_type is matched here.
#include "common.h"

namespace Archetype {

struct MineDropper {
    virtual AClassType get_class_type() const;
};

// Returns the class-type tag 0x12 -- emitted as `mov eax, 0x12; ret`.
AClassType MineDropper::get_class_type() const { return (AClassType)0x12; }

} // namespace Archetype
