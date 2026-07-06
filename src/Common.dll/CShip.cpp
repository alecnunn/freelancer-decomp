// CShip -- a controllable ship. Derives CObject<-CSimple<-CEqObj<-CShip; own
// fields from ~0x21c. Modeled flat (offset-based bodies); the leading pad
// includes the vftable pointer's 4 bytes so fields land at their real offsets.
#include "common.h"
#include "archetype.h"

enum BayState { };
enum StrafeDir { };
struct IObjRW;

struct CShip {
    unsigned char  _pad_0x00[0x88];    // +0x00 .. +0x88  vftable + EngineObject base
    Archetype::Ship* m_arch;           // +0x88  ship archetype
    unsigned char  _pad_0x8c[0x194];   // +0x8c .. +0x220
    char*          m_target;           // +0x220 stored target (get_target returns it - 8)
    unsigned char  _pad_0x224[4];      // +0x224
    unsigned short m_sub_target;       // +0x228
    unsigned char  _pad_0x22a[0x22];   // +0x22a .. +0x24c
    Vector         m_axis_throttle;    // +0x24c
    unsigned char  _pad_0x258[0x40];   // +0x258 .. +0x298
    StrafeDir      m_strafe_dir;       // +0x298
    float          m_throttle;         // +0x29c
    float          m_thrust_power;     // +0x2a0
    float          m_max_thrust_power; // +0x2a4
    unsigned char  _pad_0x2a8[4];      // +0x2a8
    BayState       m_bay_state;        // +0x2ac

    BayState get_bay_state() const;
    float get_throttle() const;
    const Vector& get_axis_throttle() const;
    float get_max_bank_angle() const;
    float get_thrust_power() const;
    float get_max_thrust_power() const;
    float get_thrust_power_ratio() const;
    unsigned short get_sub_target() const;
    IObjRW* get_target() const;
    StrafeDir get_strafe_dir() const;
};

BayState CShip::get_bay_state() const { return m_bay_state; }
float CShip::get_throttle() const { return m_throttle; }
const Vector& CShip::get_axis_throttle() const { return m_axis_throttle; }
float CShip::get_max_bank_angle() const { return m_arch->max_bank_angle; }
float CShip::get_thrust_power() const { return m_thrust_power; }
float CShip::get_max_thrust_power() const { return m_max_thrust_power; }
float CShip::get_thrust_power_ratio() const {
    if (m_max_thrust_power <= 0.0f)
        return 0.0f;
    return m_thrust_power / m_max_thrust_power;
}
unsigned short CShip::get_sub_target() const { return m_sub_target; }
IObjRW* CShip::get_target() const {
    if (m_target != 0)
        return (IObjRW*)(m_target - 8);
    return 0;
}

StrafeDir CShip::get_strafe_dir() const { return m_strafe_dir; }
