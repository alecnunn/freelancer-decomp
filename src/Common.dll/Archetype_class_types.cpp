// Archetype::* get_class_type -- each concrete equipment/object archetype
// overrides the virtual get_class_type() to return its constant AClassType tag
// (mov eax,IMM; ret). Modeled as lone public-virtual const members so MSVC
// mangles them to ?get_class_type@X@Archetype@@UBE?AW4AClassType@2@XZ and they
// pair automatically. Values are the raw tags from the original binary.
#include "common.h"

namespace Archetype {

struct Asteroid { virtual AClassType get_class_type() const; };
AClassType Asteroid::get_class_type() const { return (AClassType)0x4; }

struct DynamicAsteroid { virtual AClassType get_class_type() const; };
AClassType DynamicAsteroid::get_class_type() const { return (AClassType)0x5; }

struct Equipment { virtual AClassType get_class_type() const; };
AClassType Equipment::get_class_type() const { return (AClassType)0x6; }

struct AttachedEquipment { virtual AClassType get_class_type() const; };
AClassType AttachedEquipment::get_class_type() const { return (AClassType)0x7; }

struct LootCrate { virtual AClassType get_class_type() const; };
AClassType LootCrate::get_class_type() const { return (AClassType)0x8; }

struct Thruster { virtual AClassType get_class_type() const; };
AClassType Thruster::get_class_type() const { return (AClassType)0xf; }

struct Launcher { virtual AClassType get_class_type() const; };
AClassType Launcher::get_class_type() const { return (AClassType)0x10; }

struct Gun { virtual AClassType get_class_type() const; };
AClassType Gun::get_class_type() const { return (AClassType)0x11; }

struct CounterMeasureDropper { virtual AClassType get_class_type() const; };
AClassType CounterMeasureDropper::get_class_type() const { return (AClassType)0x13; }

struct Scanner { virtual AClassType get_class_type() const; };
AClassType Scanner::get_class_type() const { return (AClassType)0x14; }

struct Light { virtual AClassType get_class_type() const; };
AClassType Light::get_class_type() const { return (AClassType)0x15; }

struct Tractor { virtual AClassType get_class_type() const; };
AClassType Tractor::get_class_type() const { return (AClassType)0x16; }

struct AttachedFXEquip { virtual AClassType get_class_type() const; };
AClassType AttachedFXEquip::get_class_type() const { return (AClassType)0x17; }

struct InternalFXEquip { virtual AClassType get_class_type() const; };
AClassType InternalFXEquip::get_class_type() const { return (AClassType)0x18; }

struct RepairDroid { virtual AClassType get_class_type() const; };
AClassType RepairDroid::get_class_type() const { return (AClassType)0x19; }

struct RepairKit { virtual AClassType get_class_type() const; };
AClassType RepairKit::get_class_type() const { return (AClassType)0x1a; }

struct ShieldBattery { virtual AClassType get_class_type() const; };
AClassType ShieldBattery::get_class_type() const { return (AClassType)0x1b; }

struct CloakingDevice { virtual AClassType get_class_type() const; };
AClassType CloakingDevice::get_class_type() const { return (AClassType)0x1c; }

struct Projectile { virtual AClassType get_class_type() const; };
AClassType Projectile::get_class_type() const { return (AClassType)0x1e; }

struct Munition { virtual AClassType get_class_type() const; };
AClassType Munition::get_class_type() const { return (AClassType)0x1f; }

struct Mine { virtual AClassType get_class_type() const; };
AClassType Mine::get_class_type() const { return (AClassType)0x20; }

struct CounterMeasure { virtual AClassType get_class_type() const; };
AClassType CounterMeasure::get_class_type() const { return (AClassType)0x21; }

struct Armor { virtual AClassType get_class_type() const; };
AClassType Armor::get_class_type() const { return (AClassType)0x22; }

} // namespace Archetype
