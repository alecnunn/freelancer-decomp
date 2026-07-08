// CNudgeEngine -- collision-avoidance steering controller (PhySys::Controller
// derived). Recovered from Common.dll; size 0x28. Applies a "nudge" velocity to
// push the ship away from obstacles. Symbol-rich unit: real member definitions
// mangle to the original symbols and pair automatically.
//
// Layout (base PhySys::Controller occupies 0x00..0x14):
//   +0x14  void*   m_controlled
//   +0x18  bool    m_active
//   +0x1c  Vector  m_nudge          (current nudge vector)
#include "common.h"

class CNudgeEngine {
public:
    unsigned char _pad_0[0x1c];   // PhySys::Controller base + m_controlled/m_active
    Vector        m_nudge;        // +0x1c

    Vector GetNudgeVec() const;
};

Vector CNudgeEngine::GetNudgeVec() const {
    return m_nudge;
}
