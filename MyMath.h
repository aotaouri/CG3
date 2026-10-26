#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Matrix4x4 MakeIdentityMatrix();
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
inline Vector3 operator*(const Vector3& v, float s)
{
    return { v.x * s, v.y * s, v.z * s };
}

inline Vector3 operator*(float s, const Vector3& v)
{
    return { v.x * s, v.y * s, v.z * s };
}

inline Vector3& operator+=(Vector3& a, const Vector3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}