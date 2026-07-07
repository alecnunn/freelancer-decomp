// TargetManager -- scripted/forced target overrides plus the player-enemy clamp.
// Recovered from Common.dll. Symbol-rich unit: real member definitions mangle
// to the original symbols and pair automatically.
//
// Layout:
//   +0x18  int           m_forced_count
//   +0x1c  unsigned int  m_forced_targets[8]   (fixed 8-slot override list)
//
// The player-enemy clamp is a pair of file-scope ints living in the delinked
// anonymous data blob at __delink_ida_data_start+0x2754 / +0x2758.
#include "common.h"

extern "C" char __delink_ida_data_start[];

class TargetManager {
public:
    unsigned char _pad_0[0x18];          // +0x00 .. +0x18
    int           m_forced_count;        // +0x18
    unsigned int  m_forced_targets[8];   // +0x1c

    // submit/remove carry correct logic but plateau below 100% under MSVC6:
    // the loop counter is reused as the return value and the scheduler places
    // the shared `xor eax,eax` / memory-increment differently (register cap).
    int submit_forced_target(unsigned int target);
    int remove_forced_target(unsigned int target);
    void set_player_enemy_clamp(int lo, int hi);
};

int TargetManager::submit_forced_target(unsigned int target) {
    int count = m_forced_count;
    if (count < 8) {
        for (int i = 0; i < count; i++) {
            if (m_forced_targets[i] == target)
                return 0;
        }
        m_forced_targets[count] = target;
        m_forced_count++;
        return 1;
    }
    return 0;
}

int TargetManager::remove_forced_target(unsigned int target) {
    int count = m_forced_count;
    int i;
    for (i = 0; i < count; i++) {
        if (m_forced_targets[i] == target)
            break;
    }
    if (i >= count)
        return 0;
    for (int j = i; j < m_forced_count - 1; j++)
        m_forced_targets[j] = m_forced_targets[j + 1];
    m_forced_count--;
    return 1;
}

void TargetManager::set_player_enemy_clamp(int lo, int hi) {
    *(int*)(__delink_ida_data_start + 0x2754) = lo;
    *(int*)(__delink_ida_data_start + 0x2758) = hi;
}
