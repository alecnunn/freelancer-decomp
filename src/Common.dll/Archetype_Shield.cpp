// Archetype::Shield -- shield equipment archetype.
// Recovered from Common.dll (symbol-rich unit): real member definitions mangle
// to the original symbols and objdiff pairs them automatically.
//
// Shield derives (Root -> Equipment -> Shield); full instance layout is size
// 0x88 with the Shield-specific fields living at 0x5c..0x84 (regen rate, hit
// pts, thresholds, ID_String x3, CacheString, ...). That layout, the two
// constructors, and the default-ctor closure are DEFERRED here because they are
// a fully inlined base-ctor chain (Archetype::Root::Root, ID_String::clear x3,
// CacheString::clear, SEH) -- they will match when the base classes land. Only
// the trivial virtual override get_class_type is emitted this pass.
#include "common.h"

namespace Archetype {

struct Shield {
    virtual AClassType get_class_type() const;
};

// ?get_class_type@Shield@Archetype@@UBE?AW4AClassType@2@XZ
// mov eax, 0xd ; ret  -- Shield's AClassType tag is 0x0d.
AClassType Shield::get_class_type() const {
    return (AClassType)0xd;
}

} // namespace Archetype
