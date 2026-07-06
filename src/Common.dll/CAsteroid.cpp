// CAsteroid -- a static asteroid instance (derives from CSimple). Symbol-rich
// unit: real member functions mangle to the original symbols and pair
// automatically. Own fields begin at 0xe8 (base CSimple occupies the rest).
// Only the trivial field accessors are implemented here; the constructors,
// destructor, init/init_physics all chain into the CSimple base and are
// deferred.
#include "common.h"

namespace CmnAsteroid { class CAsteroidField; }

struct CAsteroid {
    unsigned char pad_0[0xe8];                       // +0x00  CSimple base
    unsigned long m_asteroid_id;                     // +0xe8
    unsigned long m_field_ec;                         // +0xec
    bool          m_is_mine;                          // +0xf0
    bool          m_is_instant_kill;                  // +0xf1
    unsigned char pad_f2[2];                          // +0xf2
    unsigned long m_field_f4;                         // +0xf4
    const CmnAsteroid::CAsteroidField* m_owner_field; // +0xf8

    unsigned long get_asteroid_id();
    bool is_mine();
    bool is_instant_kill();
    const CmnAsteroid::CAsteroidField* get_owner_field();
};

unsigned long CAsteroid::get_asteroid_id() { return m_asteroid_id; }
bool CAsteroid::is_mine() { return m_is_mine; }
bool CAsteroid::is_instant_kill() { return m_is_instant_kill; }
const CmnAsteroid::CAsteroidField* CAsteroid::get_owner_field() { return m_owner_field; }
