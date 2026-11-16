#include "Input.h"
#include "WinApp.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(WinApp* winApp)
{
	HRESULT result;

	// DirectInputのインスタンス生成
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイス生成
	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard_->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	// 前回のキー入力を保存
	memcpy(keyPre_, key_, sizeof(key_));

	// キーボード情報の取得開始
	keyboard_->Acquire();

	// 全キーの入力状態を取得する
	keyboard_->GetDeviceState(sizeof(key_), key_);
}

bool Input::PushKey(BYTE keyNumber) const
{
	// 指定キーを押していればtrueを返す
	return (key_[keyNumber] & 0x80) != 0;
}

bool Input::TriggerKey(BYTE keyNumber) const
{
	// 前回は押していなくて、今回は押していればtrueを返す
	return (key_[keyNumber] & 0x80) != 0 && (keyPre_[keyNumber] & 0x80) == 0;
}