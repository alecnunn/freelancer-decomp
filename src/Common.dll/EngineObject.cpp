// EngineObject -- base for engine-backed world objects (a spatial transform,
// bounding sphere, and an engine instance handle). Recovered from Common.dll
// (symbol-rich unit); size 0x4c. The public thiscall accessors read/write the
// locally cached transform, while the private __stdcall virtuals are the engine
// callback overrides (this is passed on the stack -- G/__stdcall mangling).
//
// Implemented here: the trivial cached-transform getters/setters (both the
// public thiscall wrappers and the private virtual overrides), the flag and
// centered-radius accessors, initialize/destroy_instance, and the empty virtual
// destructor. Deferred (see notes): the default ctor (double-inits an inlined
// Matrix/Vector), the compiler-generated copy ctor/assign, update_tree and the
// private set_centered_radius (both call through another class's vtable at a
// fixed slot), and get_velocity/get_angular_velocity (function-local statics).
#include "EngineObject.h"

EngineObject::~EngineObject() {}

// ---- public thiscall accessors -------------------------------------------
const float EngineObject::get_radius() const { return m_radius; }
const Vector& EngineObject::get_position() const { return m_position; }
void EngineObject::set_position(const Vector& v) { m_position = v; }
void EngineObject::set_orientation(const Matrix& m) { m_orientation = m; }
void EngineObject::set_transform(const Transform& t) {
    *(Transform*)&m_orientation = t;
}

// ---- private __stdcall engine-callback overrides --------------------------
void __stdcall EngineObject::initialize_instance(long id) { m_instance_id = id; }
void __stdcall EngineObject::destroy_instance(long) { m_instance_id = -1; }

void __stdcall EngineObject::set_position(long, const Vector& v) { m_position = v; }
const Vector& __stdcall EngineObject::get_position(long) const { return m_position; }

void __stdcall EngineObject::set_orientation(long, const Matrix& m) { m_orientation = m; }
const Matrix& __stdcall EngineObject::get_orientation(long) const { return m_orientation; }

void __stdcall EngineObject::set_transform(long, const Transform& t) {
    *(Transform*)&m_orientation = t;
}

void __stdcall EngineObject::get_centered_radius(long, float* radius, Vector* center) const {
    *radius = m_radius;
    *center = m_center;
}
void __stdcall EngineObject::set_centered_radius(long, float radius, const Vector& center) {
    m_radius = radius;
    m_center = center;
}

unsigned long __stdcall EngineObject::get_instance_flags(long) const { return m_instance_flags; }
void __stdcall EngineObject::set_instance_flags(long, unsigned long flags) { m_instance_flags = flags; }
