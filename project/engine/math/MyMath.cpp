#pragma once
#include"MyMath.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

// アフィン変換行列を作成する関数
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
    // 1. スケーリング行列 (S)
    // 2. X, Y, Z 軸の回転行列 (Rx, Ry, Rz)
    // 3. 平行移動行列 (T)
    // これらを順に合成した結果（T * Rz * Rx * Ry * S など）を計算します

    Matrix4x4 result;

    // 例：X, Y, Z回転角から合成行列を直接組み立てるパターン（Z -> X -> Y の回転順序などの場合）
    float cx = cosf(rotate.x), sx = sinf(rotate.x);
    float cy = cosf(rotate.y), sy = sinf(rotate.y);
    float cz = cosf(rotate.z), sz = sinf(rotate.z);

    // 行列要素の計算 (行優先/列優先や回転順序の指定に合わせて適宜調整してください)
    result.m[0][0] = scale.x * (cy * cz + sy * sx * sz);
    result.m[0][1] = scale.x * (cy * sz - sy * sx * cz);
    result.m[0][2] = scale.x * (sy * cx);
    result.m[0][3] = 0.0f;

    result.m[1][0] = scale.y * (-cx * sz);
    result.m[1][1] = scale.y * (cx * cz);
    result.m[1][2] = scale.y * (sx);
    result.m[1][3] = 0.0f;

    result.m[2][0] = scale.z * (-sy * cz + cy * sx * sz);
    result.m[2][1] = scale.z * (-sy * sz - cy * sx * cz);
    result.m[2][2] = scale.z * (cy * cx);
    result.m[2][3] = 0.0f;

    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    result.m[3][3] = 1.0f;

    return result;
}


Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate)
{
    float cx = std::cos(rotate.x), sx = std::sin(rotate.x);
    float cy = std::cos(rotate.y), sy = std::sin(rotate.y);
    float cz = std::cos(rotate.z), sz = std::sin(rotate.z);

    Matrix4x4 result;

    result.m[0][0] = cy * cz + sy * sx * sz;
    result.m[0][1] = cy * sz - sy * sx * cz;
    result.m[0][2] = sy * cx;
    result.m[0][3] = 0.0f;

    result.m[1][0] = -cx * sz;
    result.m[1][1] = cx * cz;
    result.m[1][2] = sx;
    result.m[1][3] = 0.0f;

    result.m[2][0] = -sy * cz + cy * sx * sz;
    result.m[2][1] = -sy * sz - cy * sx * cz;
    result.m[2][2] = cy * cx;
    result.m[2][3] = 0.0f;

    result.m[3][0] = 0.0f;
    result.m[3][1] = 0.0f;
    result.m[3][2] = 0.0f;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
    Matrix4x4 result;

    // 単位行列（対角線を 1）に設定
    result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
    result.m[1][0] = 0.0f; result.m[1][1] = 1.0f; result.m[1][2] = 0.0f; result.m[1][3] = 0.0f;
    result.m[2][0] = 0.0f; result.m[2][1] = 0.0f; result.m[2][2] = 1.0f; result.m[2][3] = 0.0f;

    // 4行目に平行移動成分（x, y, z）をセット
    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result.m[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k)
            {
                result.m[row][col] += m1.m[row][k] * m2.m[k][col];
            }
        }
    }

    return result;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m)
{
    Vector3 result;

    // 平行移動成分（m[3][0]~m[3][2]）を除外して回転・拡大のみ適用
    result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];

    return result;
}

Matrix4x4 MakeIdentityMatrix()
{
    Matrix4x4 result;

    result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
    result.m[1][0] = 0.0f; result.m[1][1] = 1.0f; result.m[1][2] = 0.0f; result.m[1][3] = 0.0f;
    result.m[2][0] = 0.0f; result.m[2][1] = 0.0f; result.m[2][2] = 1.0f; result.m[2][3] = 0.0f;
    result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 MakeRotateXMatrix(float radian)
{
    Matrix4x4 result;

    float c = std::cos(radian);
    float s = std::sin(radian);

    result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
    result.m[1][0] = 0.0f; result.m[1][1] = c;    result.m[1][2] = s;    result.m[1][3] = 0.0f;
    result.m[2][0] = 0.0f; result.m[2][1] = -s;   result.m[2][2] = c;    result.m[2][3] = 0.0f;
    result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 MakeRotateYMatrix(float radian)
{
    Matrix4x4 result;

    float c = std::cos(radian);
    float s = std::sin(radian);

    result.m[0][0] = c;    result.m[0][1] = 0.0f; result.m[0][2] = -s;   result.m[0][3] = 0.0f;
    result.m[1][0] = 0.0f; result.m[1][1] = 1.0f; result.m[1][2] = 0.0f; result.m[1][3] = 0.0f;
    result.m[2][0] = s;    result.m[2][1] = 0.0f; result.m[2][2] = c;    result.m[2][3] = 0.0f;
    result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;

    return result;
}