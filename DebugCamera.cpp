#include "DebugCamera.h"
#include "MyMath.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <windows.h>

void DebugCamera::Initialize()
{
    
    // 累積回転行列を単位行列で初期化
    matRot_ = MakeIdentityMatrix();
    translation_ = { 0.0f, 0.0f, -50.0f };

}

void DebugCamera::Update(const BYTE* key)
{
    // --- 1. 今回の回転量を計算 ---
    float rotX = 0.0f;
    float rotY = 0.0f;

    if (key[DIK_UP])
    {
        rotX -= 0.02f; // 上を向く
    }
    if (key[DIK_DOWN])
    {
        rotX += 0.02f; // 下を向く
    }
    if (key[DIK_LEFT])
    {
        rotY -= 0.02f; // 左を向く
    }
    if (key[DIK_RIGHT])
    {
        rotY += 0.02f; // 右を向く
    }

    // --- 2. 追加回転分の回転行列を作成 ---
    Matrix4x4 matRotDelta = MakeIdentityMatrix();

    // ※演習の指定に合わせて * 演算子 または Multiply 関数を使用してください
    // 例: Multiply を使う場合
    matRotDelta = Multiply(matRotDelta, MakeRotateXMatrix(rotX));
    matRotDelta = Multiply(matRotDelta, MakeRotateYMatrix(rotY));

    // --- 3. 累積回転行列を合成 ---
    matRot_ = Multiply(matRotDelta, matRot_);

    // --- 4. カメラの移動処理 ---
    if (key[DIK_W])
    {
        const float speed = 0.2f;
        Vector3 move = { 0.0f, 0.0f, speed };
        move = TransformNormal(move, matRot_);

        translation_.x += move.x;
        translation_.y += move.y;
        translation_.z += move.z;
    }

    if (key[DIK_D])
    {
        const float speed = 0.2f;
        Vector3 move = { speed, 0.0f, 0.0f };
        move = TransformNormal(move, matRot_);

        translation_.x += move.x;
        translation_.y += move.y;
        translation_.z += move.z;
    }

    // --- 5. ビュー行列の更新 ---
    Matrix4x4 matTrans = MakeTranslateMatrix(translation_);
    Matrix4x4 worldMatrix = Multiply(matRot_, matTrans);

    viewMatrix_ = Inverse(worldMatrix);
}