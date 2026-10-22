#pragma once
#include <windows.h>
#include <cstdint>

class WinApp
{
public:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Initialize();

	void Update();

	//クライアント領域のサイズ
	static const  int32_t kClientWidth = 1280;
	static	const int32_t kClientHeight = 720;

private:

};

