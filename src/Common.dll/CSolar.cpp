// CSolar -- a fixed/solar-system object (planet, station, gate, ring, ...).
// Derives CObject<-CSimple<-CEqObj<-CSolar; own fields from ~0x1a8, plus it
// reuses the inherited type-flags word at +0xe0. Modeled flat; the leading pad
// includes the vftable pointer so fields land at their real offsets.
#include "common.h"

struct CSolar {
    unsigned char _pad_0x00[0xe0];      // +0x00 .. +0xe0  vftable + base subobjects
    unsigned int  m_type_flags;         // +0xe0  (bitfield: planetary/gate/ring/...)
    unsigned char _pad_0xe4[0xc4];      // +0xe4 .. +0x1a8
    bool          m_destructible;       // +0x1a8
    bool          m_dynamic;            // +0x1a9
    unsigned char _pad_0x1aa[2];        // +0x1aa
    float         m_atmosphere_range;   // +0x1ac
    ID_String     m_loadout;            // +0x1b0
    unsigned int  m_dest_system;        // +0x1b4
    ID_String     m_dest_gate;          // +0x1b8
    unsigned char _pad_0x1bc[0x1c];     // +0x1bc .. +0x1d8
    unsigned int  m_prev_trade_ring;    // +0x1d8
    unsigned int  m_next_trade_ring;    // +0x1dc
    unsigned int  m_tradelane_space_name; // +0x1e0
    unsigned char m_visit_value;        // +0x1e4
    unsigned char _pad_0x1e5[3];        // +0x1e5
    ID_String     m_parent_nickname;    // +0x1e8

    bool is_planetary() const;
    bool is_system_gate() const;
    bool is_waypoint() const;
    bool is_lane_ring() const;
    bool is_destructible() const;
    bool is_dynamic() const;
    float get_atmosphere_range() const;
    const ID_String& get_loadout() const;
    unsigned int get_dest_system() const;
    unsigned int get_prev_trade_ring() const;
    const ID_String& get_dest_gate() const;
    unsigned int get_next_trade_ring() const;
    unsigned int get_tradelane_space_name() const;
    unsigned char GetVisitValue() const;
    const ID_String& GetParentNickname() const;
};

bool CSolar::is_planetary() const { return (m_type_flags & 7) != 0; }
bool CSolar::is_system_gate() const { return m_type_flags == (m_type_flags & 0xc40); }
bool CSolar::is_waypoint() const { return (m_type_flags >> 9) & 1; }
bool CSolar::is_lane_ring() const { return (m_type_flags >> 7) & 1; }
bool CSolar::is_destructible() const { return m_destructible; }
bool CSolar::is_dynamic() const { return m_dynamic; }
float CSolar::get_atmosphere_range() const { return m_atmosphere_range; }
const ID_String& CSolar::get_loadout() const { return m_loadout; }
unsigned int CSolar::get_dest_system() const { return m_dest_system; }
unsigned int CSolar::get_prev_trade_ring() const { return m_prev_trade_ring; }
const ID_String& CSolar::get_dest_gate() const { return m_dest_gate; }
unsigned int CSolar::get_next_trade_ring() const { return m_next_trade_ring; }
unsigned int CSolar::get_tradelane_space_name() const { return m_tradelane_space_name; }
unsigned char CSolar::GetVisitValue() const { return m_visit_value; }
const ID_String& CSolar::GetParentNickname() const { return m_parent_nickname; }
