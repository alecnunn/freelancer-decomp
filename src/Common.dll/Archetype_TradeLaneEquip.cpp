// Archetype::TradeLaneEquip -- trade-lane ring equipment archetype.
// Recovered from Common.dll (symbol-rich unit): real member definitions mangle
// to the original symbols and objdiff pairs them automatically.
//
// TradeLaneEquip derives (Root -> Equipment -> TradeLaneEquip). The main ctor
// (0x626da30) forwards to Archetype::Equipment::Equipment(ICliObj*) then sets
// the vftable; the copy ctor (0x626da60) is a flattened base-copy chain
// (Archetype::Root::Root + field copies at +0x5c..+0x6c); the default-ctor
// closure (0x626dae0) just calls the main ctor with null. All three are
// DEFERRED because they call into other classes -- they will match when the
// Equipment/Root base classes land. Only the trivial virtual override
// get_class_type is emitted this pass.
#include "common.h"

namespace Archetype {

struct TradeLaneEquip {
    virtual AClassType get_class_type() const;
};

// ?get_class_type@TradeLaneEquip@Archetype@@UBE?AW4AClassType@2@XZ
// mov eax, 0x1d ; ret  -- TradeLaneEquip's AClassType tag is 0x1d.
AClassType TradeLaneEquip::get_class_type() const {
    return (AClassType)0x1d;
}

} // namespace Archetype
