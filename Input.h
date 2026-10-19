#pragma once
#include <Windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>


class Input
{

public:

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Initialize(HINSTANCE wc, HWND hwnd);

	void Update();

private:
	//キーボードデバイス
	ComPtr<IDirectInputDevice8> keyboard;

};

