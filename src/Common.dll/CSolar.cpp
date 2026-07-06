// CSolar -- a fixed/solar-system object (planet, station, gate, ring, ...).
// Derives CObject<-CSimple<-CEqObj<-CSolar; own fields from +0x1a8 (CEqObj's
// size). CEqObj is defined earlier in the unity build. The is_planetary/gate/
// ring predicates read the inherited CSimple::m_type@0xe0 as a bitfield.
#include "common.h"

struct CSolar : CEqObj {
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

bool CSolar::is_planetary() const { return (m_type & OBJ_PLANETARY_BODY) != 0; }
bool CSolar::is_system_gate() const { return m_type == (m_type & OBJ_SYSTEM_GATE); }
bool CSolar::is_waypoint() const { return (m_type >> 9) & 1; }   // OBJ_WAYPOINT (bit 9)
bool CSolar::is_lane_ring() const { return (m_type >> 7) & 1; }  // OBJ_TRADELANE_RING (bit 7)
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
