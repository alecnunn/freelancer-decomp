// CShip -- a controllable ship. Derives CObject<-CSimple<-CEqObj<-CShip; own
// fields from +0x1a8 (CEqObj's size). CEqObj is defined earlier in the unity
// build. The ship archetype is the inherited CObject::m_arch@0x88 (a Root* that
// actually points at an Archetype::Ship).
#include "common.h"
#include "archetype.h"

enum BayState { };
enum StrafeDir { };
struct IObjRW;

struct CShip : CEqObj {
    unsigned char  _pad_0x1a8[0x40];   // +0x1a8 .. +0x1e8
    Vector         m_follow_offset;    // +0x1e8
    unsigned char  _pad_0x1f4[0x2c];   // +0x1f4 .. +0x220
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
    unsigned char  _pad_0x2b0[8];      // +0x2b0
    float          m_tradelane_speed;  // +0x2b8
    bool           m_using_tradelane;  // +0x2bc
    unsigned char  _pad_0x2bd[3];      // +0x2bd
    float          m_angular_drag_factor; // +0x2c0
    bool           m_gun_stats_dirty;  // +0x2c4

    BayState get_bay_state() const;
    void use_tradelane(bool use);
    void set_thrust_power(float p);
    void set_sub_target(unsigned short t);
    void set_tradelane_speed(float s);
    void set_angular_drag_factor(float f);
    void set_gun_stats_dirty();
    void set_follow_offset(const Vector& offset);
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
void CShip::use_tradelane(bool use) { m_using_tradelane = use; }
void CShip::set_thrust_power(float p) { m_thrust_power = p; }
void CShip::set_sub_target(unsigned short t) { m_sub_target = t; }
void CShip::set_tradelane_speed(float s) { m_tradelane_speed = s; }
void CShip::set_angular_drag_factor(float f) { m_angular_drag_factor = f; }
void CShip::set_gun_stats_dirty() { m_gun_stats_dirty = true; }
void CShip::set_follow_offset(const Vector& offset) { m_follow_offset = offset; }
float CShip::get_throttle() const { return m_throttle; }
const Vector& CShip::get_axis_throttle() const { return m_axis_throttle; }
float CShip::get_max_bank_angle() const {
    return ((const Archetype::Ship*)m_arch)->max_bank_angle;
}
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
