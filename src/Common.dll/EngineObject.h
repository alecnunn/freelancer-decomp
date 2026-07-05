// EngineObject -- base for engine-backed world objects (a spatial transform,
// bounding sphere, and an engine instance handle). Recovered from Common.dll;
// size 0x4c, with the engine-callback vtable. Shared so CObject (and thus the
// whole CObject->CSimple->... tree) can derive from it.
#ifndef COMMON_DLL_ENGINEOBJECT_H
#define COMMON_DLL_ENGINEOBJECT_H

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

#endif // COMMON_DLL_ENGINEOBJECT_H
