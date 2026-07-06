// Archetype::* get_class_type -- each concrete equipment/object archetype
// overrides the virtual get_class_type() to return its constant AClassType tag
// (mov eax,IMM; ret). The struct declarations live in archetype.h (deriving
// from Archetype::Root); here we only define the method bodies, which MSVC
// mangles to ?get_class_type@X@Archetype@@UBE?AW4AClassType@2@XZ and pair
// automatically. Values are the raw tags from the original binary.
#include "common.h"
#include "archetype.h"

namespace Archetype {

AClassType Asteroid::get_class_type() const { return (AClassType)0x4; }
AClassType DynamicAsteroid::get_class_type() const { return (AClassType)0x5; }
AClassType Equipment::get_class_type() const { return (AClassType)0x6; }
AClassType AttachedEquipment::get_class_type() const { return (AClassType)0x7; }
AClassType LootCrate::get_class_type() const { return (AClassType)0x8; }
AClassType Thruster::get_class_type() const { return (AClassType)0xf; }
AClassType Launcher::get_class_type() const { return (AClassType)0x10; }
AClassType Gun::get_class_type() const { return (AClassType)0x11; }
AClassType CounterMeasureDropper::get_class_type() const { return (AClassType)0x13; }
AClassType Scanner::get_class_type() const { return (AClassType)0x14; }
AClassType Light::get_class_type() const { return (AClassType)0x15; }
AClassType Tractor::get_class_type() const { return (AClassType)0x16; }
AClassType AttachedFXEquip::get_class_type() const { return (AClassType)0x17; }
AClassType InternalFXEquip::get_class_type() const { return (AClassType)0x18; }
AClassType RepairDroid::get_class_type() const { return (AClassType)0x19; }
AClassType RepairKit::get_class_type() const { return (AClassType)0x1a; }
AClassType ShieldBattery::get_class_type() const { return (AClassType)0x1b; }
AClassType CloakingDevice::get_class_type() const { return (AClassType)0x1c; }
AClassType Projectile::get_class_type() const { return (AClassType)0x1e; }
AClassType Munition::get_class_type() const { return (AClassType)0x1f; }
AClassType Mine::get_class_type() const { return (AClassType)0x20; }
AClassType CounterMeasure::get_class_type() const { return (AClassType)0x21; }
AClassType Armor::get_class_type() const { return (AClassType)0x22; }

} // namespace Archetype
