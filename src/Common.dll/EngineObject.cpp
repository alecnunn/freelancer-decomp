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
#include "common.h"

struct EngineObject {
    long          m_instance_id;    // +0x04  engine instance handle (-1 == none)
    Matrix        m_orientation;    // +0x08  cached orientation (3x3)
    Vector        m_position;       // +0x2c  cached position
    float         m_radius;         // +0x38  bounding-sphere radius
    Vector        m_center;         // +0x3c  bounding-sphere center
    unsigned long m_instance_flags; // +0x48

    virtual ~EngineObject();

    const float    get_radius() const;
    const Vector&  get_position() const;
    void           set_position(const Vector& v);
    void           set_orientation(const Matrix& m);
    void           set_transform(const Transform& t);

private:
    virtual void           __stdcall initialize_instance(long id);
    virtual void           __stdcall destroy_instance(long id);
    virtual void           __stdcall set_position(long id, const Vector& v);
    virtual const Vector&  __stdcall get_position(long id) const;
    virtual void           __stdcall set_orientation(long id, const Matrix& m);
    virtual const Matrix&  __stdcall get_orientation(long id) const;
    virtual void           __stdcall set_transform(long id, const Transform& t);
    virtual void           __stdcall get_centered_radius(long id, float* radius, Vector* center) const;
    virtual void           __stdcall set_centered_radius(long id, float radius, const Vector& center);
    virtual unsigned long  __stdcall get_instance_flags(long id) const;
    virtual void           __stdcall set_instance_flags(long id, unsigned long flags);
};

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
