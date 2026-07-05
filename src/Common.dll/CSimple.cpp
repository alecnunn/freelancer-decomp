// CSimple -- base class for the simulatable-object hierarchy (CObject-derived;
// itself the base of CEqObj/CSolar/CShip/... via further derivation). Large
// polymorphic class recovered from Common.dll; own fields begin at +0x88 atop
// the base subobjects. Only the offsets touched by matched methods are named.
#include "common.h"

namespace Archetype { struct Root; }
struct IObjDB;

struct CSimple {
    // implicit vftable pointer at +0x00
    unsigned char    _pad_0x04[0x84];  // +0x04  base subobjects / unmodeled fields
    Archetype::Root* m_arch;           // +0x88  archetype root (max hit pts at +0x1c)
    unsigned char    _pad_0x8c[0x14];  // +0x8c
    unsigned char    m_flags;          // +0xa0  bit0 = targetable (byte-accessed)
    unsigned char    _pad_0xa1[3];     // +0xa1
    void*            m_scanner_src;    // +0xa4  object queried for scanner interference
    float            m_scanner_scale;  // +0xa8
    IObjDB*          m_object_db;      // +0xac
    unsigned int     m_id;             // +0xb0
    unsigned int     m_owner_player;   // +0xb4
    float            m_hit_pts;        // +0xb8
    unsigned char    _pad_0xbc[0x24];  // +0xbc
    unsigned int     m_type;           // +0xe0

    const unsigned int& get_id() const;
    unsigned int get_type() const;
    unsigned int GetOwnerPlayer() const;
    void SetOwnerPlayer(unsigned int player);
    virtual bool is_targetable() const;
    IObjDB* get_object_database() const;
    float get_hit_pts() const;
    virtual void set_hit_pts(float hp);
    float get_max_hit_pts() const;
    float get_relative_health() const;
};

const unsigned int& CSimple::get_id() const { return m_id; }
unsigned int CSimple::get_type() const { return m_type; }
unsigned int CSimple::GetOwnerPlayer() const { return m_owner_player; }
void CSimple::SetOwnerPlayer(unsigned int player) { m_owner_player = player; }
bool CSimple::is_targetable() const { return m_flags & 1; }
IObjDB* CSimple::get_object_database() const { return m_object_db; }
float CSimple::get_hit_pts() const { return m_hit_pts; }
void CSimple::set_hit_pts(float hp) { m_hit_pts = hp; }
float CSimple::get_max_hit_pts() const { return *(const float*)((const char*)m_arch + 0x1c); }
float CSimple::get_relative_health() const {
    return m_hit_pts / *(const float*)((const char*)m_arch + 0x1c);
}
