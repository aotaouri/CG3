#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <windows.h>

class DebugCamera
{
public:

	void Initialize();

	void Update(const BYTE* key);


private:

	Vector3 translation_ = { 0, 0, -50 };

	Matrix4x4 matRot_;

	// ビュー行列
	Matrix4x4 viewMatrix_;
	// 射影行列
	Matrix4x4 projectionMatrix_;

};

