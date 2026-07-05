// CEEngine -- a mounted engine. Hierarchy CEquip<-...<-CEEngine; reads the
// engine archetype (inherited m_arch@0x0c) for thrust/drag/power values, plus
// its own cruise state. Accessors are non-virtual (offset-based bodies).
#include "common.h"

namespace EngineEquipConsts { extern float CRUISE_DRAG; }

struct CEEngine {
    // vftable ptr + base subobjects fill 0x00..0x0c
    unsigned char _pad_0x00[0xc];      // +0x00 .. +0x0c
    void*         m_arch;              // +0x0c  engine archetype
    unsigned char _pad_0x10[0x40];     // +0x10 .. +0x50
    float         m_cruise_charge_elapsed; // +0x50
    bool          m_cruise_engaged;    // +0x54

    bool  IsCruiseEngaged() const;
    float GetCruiseChargeTime() const;
    float GetCruiseChargeTimeElapsed() const;
    float GetCruisePowerDraw() const;
    float GetLinearDrag() const;
    float GetCruiseDrag() const;
    float GetThrust(float throttle) const;
};

bool  CEEngine::IsCruiseEngaged() const { return m_cruise_engaged; }
float CEEngine::GetCruiseChargeTime() const { return *(const float*)((const char*)m_arch + 0x80); }
float CEEngine::GetCruiseChargeTimeElapsed() const { return m_cruise_charge_elapsed; }
float CEEngine::GetCruisePowerDraw() const { return *(const float*)((const char*)m_arch + 0x7c); }
float CEEngine::GetLinearDrag() const { return *(const float*)((const char*)m_arch + 0x74); }
float CEEngine::GetCruiseDrag() const {
    float base = *(const float*)((const char*)m_arch + 0x74);
    return base + EngineEquipConsts::CRUISE_DRAG;
}
float CEEngine::GetThrust(float throttle) const {
    if (throttle > 0.0f)
        throttle *= *(const float*)((const char*)m_arch + 0x88);
    return throttle * *(const float*)((const char*)m_arch + 0x70);
}
