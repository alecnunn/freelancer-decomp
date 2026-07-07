// x86math.dll -- 3x3 matrix / vector transform routines.
// These are __stdcall functions with the engine `this` passed as an unused
// leading stack slot, then (out, matrix, vector). Each computes out = M * v
// row by row (out.c = M.row_c . v). All unnamed (sub_XXX); claimed to the C++
// symbols below.
#include "x86math.h"

// sub_6F71830: out = M * v   (rotate a vector by a 3x3 matrix)
// 93.8%: correct; the residual is a /G6 scheduling cap -- the original groups
// all three pointer loads (M, v, out) before the FP, MSVC6 here defers the out
// load past the first fmul. Same class as the loop-head-align caps.
extern "C" int __stdcall x86m_rotate(int /*self*/, Vector* out, const Matrix* M, const Vector* v) {
    out->x = M->m[0] * v->x + M->m[1] * v->y + M->m[2] * v->z;
    out->y = M->m[3] * v->x + M->m[4] * v->y + M->m[5] * v->z;
    out->z = M->m[6] * v->x + M->m[7] * v->y + M->m[8] * v->z;
    return 0;
}

// sub_6F718F0: out = transpose(M) * v   (out.c = column_c(M) . v)
extern "C" int __stdcall x86m_rotate_transpose(int /*self*/, Vector* out, const Matrix* M, const Vector* v) {
    out->x = M->m[0] * v->x + M->m[3] * v->y + M->m[6] * v->z;
    out->y = M->m[1] * v->x + M->m[4] * v->y + M->m[7] * v->z;
    out->z = M->m[2] * v->x + M->m[5] * v->y + M->m[8] * v->z;
    return 0;
}

// sub_6F71890: out = M * v + translation   (affine transform a point)
extern "C" int __stdcall x86m_transform(int /*self*/, Vector* out, const Transform* tf, const Vector* v) {
    out->x = tf->m[0] * v->x + tf->m[1] * v->y + tf->m[2] * v->z + tf->t[0];
    out->y = tf->m[3] * v->x + tf->m[4] * v->y + tf->m[5] * v->z + tf->t[1];
    out->z = tf->m[6] * v->x + tf->m[7] * v->y + tf->m[8] * v->z + tf->t[2];
    return 0;
}

// sub_6F715B0: out = s * M   (scale every element of a 3x3 matrix)
extern "C" int __stdcall x86m_scale(int /*self*/, Matrix* out, const Matrix* M, float s) {
    out->m[0] = s * M->m[0];
    out->m[1] = s * M->m[1];
    out->m[2] = s * M->m[2];
    out->m[3] = s * M->m[3];
    out->m[4] = s * M->m[4];
    out->m[5] = s * M->m[5];
    out->m[6] = s * M->m[6];
    out->m[7] = s * M->m[7];
    out->m[8] = s * M->m[8];
    return 0;
}

// sub_6F71620: determinant of a 3x3 matrix
extern "C" float __stdcall x86m_det(int /*self*/, const Matrix* M) {
    return M->m[6] * M->m[1] * M->m[5] + M->m[2] * M->m[3] * M->m[7] + M->m[8] * M->m[0] * M->m[4]
         - M->m[0] * M->m[7] * M->m[5] - M->m[8] * M->m[1] * M->m[3] - M->m[6] * M->m[2] * M->m[4];
}
