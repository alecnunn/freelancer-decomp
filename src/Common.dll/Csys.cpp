// Csys -- a coordinate system: a position (Vector) plus an orientation
// (Matrix). Size 0x30. Note the field order is the REVERSE of Transform
// (which stores orientation first, position second); get_transform/
// set_transform bridge the two layouts.
//
// Recovered from Common.dll. Symbol-rich unit: real member functions mangle
// to the original symbols and pair automatically.
#include "common.h"

struct Csys {
    Vector m_position;     // +0x00
    Matrix m_orientation;  // +0x0c

    Csys();

    void set_identity();
    void init(const Vector& v, const Matrix& m);
    Transform get_transform() const;
    void set_transform(const Transform& t);
};

// Default ctor: empty body (just returns). Note: not present in the delinked
// target (inlined at every call site), so it does not pair -- kept for
// completeness of the class definition.
Csys::Csys() {}

void Csys::set_identity() {
    Vector zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    m_position = zero;
    m_orientation.d[2][2] = 1.0f;
    m_orientation.d[1][1] = 1.0f;
    m_orientation.d[0][0] = 1.0f;
    m_orientation.d[2][1] = 0.0f;
    m_orientation.d[2][0] = 0.0f;
    m_orientation.d[1][2] = 0.0f;
    m_orientation.d[1][0] = 0.0f;
    m_orientation.d[0][2] = 0.0f;
    m_orientation.d[0][1] = 0.0f;
}

void Csys::init(const Vector& v, const Matrix& m) {
    m_position = v;
    m_orientation = m;
}

Transform Csys::get_transform() const {
    Transform t;
    t.orientation = m_orientation;
    t.position = m_position;
    return t;
}

void Csys::set_transform(const Transform& t) {
    m_position = t.position;
    m_orientation = t.orientation;
}
