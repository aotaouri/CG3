#pragma once

class Vector3
{
public:
    float x;
    float y;
    float z;

    // デフォルトコンストラクタ（引数なしで生成された場合）
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    // 3つの値を受け取るコンストラクタ
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};