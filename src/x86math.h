// x86math.dll -- shared types for the scalar FPU vector-math library.
#ifndef X86MATH_H
#define X86MATH_H

// The core 3-component vector the library operates on (x@0, y@4, z@8).
//
// The library is a family of specialised partial dot-product routines. Each
// takes two vectors: "a" and "b". One-operand routines take a single vector by
// pointer on the stack (free __stdcall functions). Two-operand routines are
// __thiscall members: `this` arrives in ecx (the "b" vector) and the other
// vector "a" is the stack parameter, so a member
// `float Vector::f(const Vector* a) const` reproduces the original load order
// (param a loaded first, this second). The names encode the computed
// expression: mul<c> = a.c*b.c, add<c> = + a.c, dot_<cc> = a.c1*b.c1+a.c2*b.c2.
struct Vector {
    float x;
    float y;
    float z;

    // sub_6F71D80: a.z * b.z
    float mulz(const Vector* a) const;
    float muly(const Vector* a) const;         // sub_6F71DC0: a.y*b.y
    float mulx(const Vector* a) const;         // sub_6F71EC0: a.x*b.x
    float mulz_addy(const Vector* a) const;    // sub_6F71DB0: a.z*b.z + a.y
    float muly_addz(const Vector* a) const;    // sub_6F71DD0: a.y*b.y + a.z
    float mulz_addx(const Vector* a) const;    // sub_6F71E20: a.z*b.z + a.x
    float muly_addx(const Vector* a) const;    // sub_6F71E70: a.y*b.y + a.x
    float mulx_addz(const Vector* a) const;    // sub_6F71ED0: a.x*b.x + a.z
    float mulx_addy(const Vector* a) const;    // sub_6F71F00: a.x*b.x + a.y
    float mulz_addyx(const Vector* a) const;   // sub_6F71E50: a.z*b.z + a.y + a.x
    float muly_addzx(const Vector* a) const;   // sub_6F71E80: a.y*b.y + a.z + a.x
    float mulx_addzy(const Vector* a) const;   // sub_6F71F10: a.x*b.x + a.z + a.y
    float dot_zy(const Vector* a) const;       // sub_6F71DE0: a.z*b.z + a.y*b.y
    float dot_zx(const Vector* a) const;       // sub_6F71EE0: a.z*b.z + a.x*b.x
    float dot_yx(const Vector* a) const;       // sub_6F71F50: a.y*b.y + a.x*b.x
    float dot_zy_addx(const Vector* a) const;  // sub_6F71EA0: a.z*b.z + a.y*b.y + a.x
    float dot_zx_addy(const Vector* a) const;  // sub_6F71F30: a.z*b.z + a.x*b.x + a.y
    float dot_yx_addz(const Vector* a) const;  // sub_6F71F70: a.y*b.y + a.x*b.x + a.z
    float dot(const Vector* a) const;          // sub_6F71F90: a.z*b.z + a.y*b.y + a.x*b.x
};

// Row-major 3x3 rotation matrix (m[0..2]=row0, [3..5]=row1, [6..8]=row2); the
// affine-transform variants read 3 extra floats at [9..11] as a translation.
struct Matrix {
    float m[9];
};

// Affine transform: 3x3 rotation (m@0..0x20) + translation (t@0x24..0x2c).
struct Transform {
    float m[9];
    float t[3];
};

#endif // X86MATH_H
