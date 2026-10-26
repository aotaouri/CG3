#pragma once
#include <Windows.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>

class Input
{

public:

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Initialize(WinApp* winApp);

	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private:
	//キーボードデバイス
	ComPtr<IDirectInputDevice8> keyboard;

	//全キーの入力状態を取得する
	BYTE key[256] = {};

	//前回の全キーの状態
	BYTE KeyPre[256] = {};

	//WIndowsAPI
	WinApp* winApp_ = nullptr;

};

