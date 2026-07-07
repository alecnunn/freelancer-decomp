// IBehaviorManager -- per-ship AI "brain" that drives the state graph and turns
// directives into concrete ship control. Recovered from Common.dll (~0x1d0).
// Symbol-rich unit: real member definitions mangle to the original symbols and
// pair automatically.
//
// Only the self-contained logic accessors are matched here; the state-graph
// machinery (set_state_graph, apply_directive, the update_current_behavior_*
// forwarders) is deferred. Relevant layout:
//   +0xb8  unsigned int  m_maneuver_mask     (bit 2<<id set == maneuver DISABLED)
//   +0xbc  bool          m_locked_maneuvers
//   +0xc4  int           m_directive_type
//   +0xc8  int           m_directive_priority
#include "common.h"

namespace pub {
namespace AI {

// Enums only need to exist for the return/argument mangling
// (?AW4OP_RTYPE@AI@pub@@ / W4DirectivePriority@AI@pub@@).
enum OP_RTYPE {
    OP_FAILURE = 0,
    OP_SUCCESS = 1,
    OP_INVALID_DIRECTIVE = 3,
};

enum DirectivePriority {
    DIRECTIVE_PRIORITY_0,
};

}  // namespace AI
}  // namespace pub

class IBehaviorManager {
public:
    unsigned char _pad_0[0xb8];             // +0x00 .. +0xb8
    unsigned int  m_maneuver_mask;          // +0xb8  disabled-maneuver bitmask
    unsigned char m_locked_maneuvers;       // +0xbc
    unsigned char _pad_bd[0xc4 - 0xbd];     // +0xbd .. +0xc4
    int           m_directive_type;         // +0xc4
    int           m_directive_priority;     // +0xc8
    unsigned char _pad_cc[0xf9 - 0xcc];     // +0xcc .. +0xf9
    bool          m_level_camera;           // +0xf9
    unsigned char _pad_fa[0x134 - 0xfa];    // +0xfa .. +0x134
    Vector        m_ship_up;                // +0x134
    Vector        m_camera_up;              // +0x140
    unsigned char _pad_14c[0x150 - 0x14c];  // +0x14c .. +0x150
    bool          m_user_turning;           // +0x150

    bool enable_maneuver(int maneuver_id, bool enable);
    bool lock_maneuvers(bool locked);
    pub::AI::OP_RTYPE set_directive_priority(pub::AI::DirectivePriority priority);

    void set_ship_up_direction(const Vector& up);
    void submit_camera_up(const Vector& up);
    void set_user_turning_input_state(bool state);
    void update_level_camera(bool level);
};

bool IBehaviorManager::enable_maneuver(int maneuver_id, bool enable) {
    if (maneuver_id != -1) {
        int bit = 2 << maneuver_id;
        unsigned int mask = m_maneuver_mask;
        if (enable)
            m_maneuver_mask = mask & ~bit;
        else
            m_maneuver_mask = mask | bit;
        return true;
    }
    return false;
}

bool IBehaviorManager::lock_maneuvers(bool locked) {
    m_locked_maneuvers = locked;
    return true;
}

pub::AI::OP_RTYPE IBehaviorManager::set_directive_priority(pub::AI::DirectivePriority priority) {
    if (m_directive_type != 0) {
        m_directive_priority = priority;
        return pub::AI::OP_SUCCESS;
    }
    return pub::AI::OP_INVALID_DIRECTIVE;
}

void IBehaviorManager::set_ship_up_direction(const Vector& up) {
    m_ship_up = up;
}

void IBehaviorManager::submit_camera_up(const Vector& up) {
    m_camera_up = up;
}

void IBehaviorManager::set_user_turning_input_state(bool state) {
    m_user_turning = state;
}

void IBehaviorManager::update_level_camera(bool level) {
    m_level_camera = level;
}
