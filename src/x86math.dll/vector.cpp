// x86math.dll -- scalar x87 FPU vector-math library.
// A family of specialised partial dot-product routines over Vector{x,y,z}.
// One-operand routines are free __stdcall functions taking the vector on the
// stack; two-operand routines are __thiscall members (this == b, param == a).
// All are unnamed (sub_XXX) in the split, so each is `fl claim`ed to the C++
// symbol under which it is reimplemented. See x86math.h for the naming scheme.
#include "x86math.h"

// ---- one-operand free functions (__stdcall, vector on the stack) ----

// sub_6F71E00: a.x
extern "C" float __stdcall x86m_vec_get_x(const Vector* a) {
    return a->x;
}
// sub_6F71D70: a->z
extern "C" float __stdcall x86m_get_z(const Vector* a) {
    return a->z;
}

// sub_6F71D90: a->y
extern "C" float __stdcall x86m_get_y(const Vector* a) {
    return a->y;
}

// sub_6F71DA0: a->z + a->y
extern "C" float __stdcall x86m_sum_zy(const Vector* a) {
    return a->z + a->y;
}

// sub_6F71E10: a->z + a->x
extern "C" float __stdcall x86m_sum_zx(const Vector* a) {
    return a->z + a->x;
}

// sub_6F71E30: a->y + a->x
extern "C" float __stdcall x86m_sum_yx(const Vector* a) {
    return a->y + a->x;
}

// sub_6F71E40: a->z + a->y + a->x
extern "C" float __stdcall x86m_sum_zyx(const Vector* a) {
    return a->z + a->y + a->x;
}

// sub_6F71DC0: a->y * y   (this == b)
float Vector::muly(const Vector* a) const {
    return a->y * y;
}

// sub_6F71EC0: a->x * x   (this == b)
float Vector::mulx(const Vector* a) const {
    return a->x * x;
}

// sub_6F71DB0: a->z * z + a->y   (this == b)
float Vector::mulz_addy(const Vector* a) const {
    return a->z * z + a->y;
}

// sub_6F71DD0: a->y * y + a->z   (this == b)
float Vector::muly_addz(const Vector* a) const {
    return a->y * y + a->z;
}

// sub_6F71E20: a->z * z + a->x   (this == b)
float Vector::mulz_addx(const Vector* a) const {
    return a->z * z + a->x;
}

// sub_6F71E70: a->y * y + a->x   (this == b)
float Vector::muly_addx(const Vector* a) const {
    return a->y * y + a->x;
}

// sub_6F71ED0: a->x * x + a->z   (this == b)
float Vector::mulx_addz(const Vector* a) const {
    return a->x * x + a->z;
}

// sub_6F71F00: a->x * x + a->y   (this == b)
float Vector::mulx_addy(const Vector* a) const {
    return a->x * x + a->y;
}

// sub_6F71E50: a->z * z + a->y + a->x   (this == b)
float Vector::mulz_addyx(const Vector* a) const {
    return a->z * z + a->y + a->x;
}

// sub_6F71E80: a->y * y + a->z + a->x   (this == b)
float Vector::muly_addzx(const Vector* a) const {
    return a->y * y + a->z + a->x;
}

// sub_6F71F10: a->x * x + a->z + a->y   (this == b)
float Vector::mulx_addzy(const Vector* a) const {
    return a->x * x + a->z + a->y;
}

// sub_6F71DE0: a->z * z + a->y * y   (this == b)
float Vector::dot_zy(const Vector* a) const {
    return a->z * z + a->y * y;
}

// sub_6F71EE0: a->z * z + a->x * x   (this == b)
float Vector::dot_zx(const Vector* a) const {
    return a->z * z + a->x * x;
}

// sub_6F71F50: a->y * y + a->x * x   (this == b)
float Vector::dot_yx(const Vector* a) const {
    return a->y * y + a->x * x;
}

// sub_6F71EA0: a->z * z + a->y * y + a->x   (this == b)
float Vector::dot_zy_addx(const Vector* a) const {
    return a->z * z + a->y * y + a->x;
}

// sub_6F71F30: a->z * z + a->x * x + a->y   (this == b)
float Vector::dot_zx_addy(const Vector* a) const {
    return a->z * z + a->x * x + a->y;
}

// sub_6F71F70: a->y * y + a->x * x + a->z   (this == b)
float Vector::dot_yx_addz(const Vector* a) const {
    return a->y * y + a->x * x + a->z;
}

// sub_6F71F90: a->z * z + a->y * y + a->x * x   (this == b)
float Vector::dot(const Vector* a) const {
    return a->z * z + a->y * y + a->x * x;
}

// sub_6F71D80: a.z * z   (this == b)
float Vector::mulz(const Vector* a) const {
    return a->z * z;
}
