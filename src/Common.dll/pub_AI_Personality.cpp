// pub::AI::Personality -- AI combat/behavior personality parameters.
// Recovered from Common.dll. Symbol-rich unit: real member functions mangle
// to the original symbols and pair automatically.
//
// Only the two trivial value queries are matched here. The class is a large
// aggregate (~0x2f8 bytes) whose default ctor initialises many float fields
// and constructs four embedded sub-structs (BuzzHeadTowardUseStruct,
// DamageReactionStruct, FormationUseStruct, JobStruct); that ctor, operator=,
// and the per-sub-struct ctors/operators are deferred (see notes below).
#include "common.h"

namespace pub {
namespace AI {

class Personality {
public:
    enum TOUGHNESS_TYPE {
        TOUGHNESS_0,
        TOUGHNESS_1,
        TOUGHNESS_2,
        TOUGHNESS_3,
        TOUGHNESS_4,
    };

    // Only the field touched by get_range_threshold_value is modelled; the
    // remainder of the object is opaque filler. m_toughness is the first int
    // of the embedded JobStruct at +0x2a0.
    unsigned char _pad_0[0x2a0];
    int           m_toughness;   // +0x2a0

    float get_range_threshold_value();
    float get_toughness_ratio(TOUGHNESS_TYPE toughness);
};

float Personality::get_range_threshold_value() {
    float threshold = 5000.0f;
    if (m_toughness == 1)
        return threshold * 0.66666666666666663;
    if (m_toughness == 2)
        return threshold * 0.33333333333333331;
    return threshold;
}

float Personality::get_toughness_ratio(TOUGHNESS_TYPE toughness) {
    switch (toughness) {
    case TOUGHNESS_0: return 0.15f;
    case TOUGHNESS_1: return 0.35f;
    case TOUGHNESS_2: return 0.65f;
    case TOUGHNESS_3: return 0.85f;
    case TOUGHNESS_4: return 1.0f;
    default:          return 0.5f;
    }
}

} // namespace AI
} // namespace pub
