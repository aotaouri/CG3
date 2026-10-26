#pragma once
#include <windows.h>
#include <cstdint>

class WinApp
{
public:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Initialize();

	void Update();

	//終了
	void Finalize();

	HWND GetHwnd() const { return hwnd; }

	//getter
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	//クライアント領域のサイズ
	static const  int32_t kClientWidth = 1280;
	static	const int32_t kClientHeight = 720;

private:

	//ウィンドウハンドル
	HWND hwnd = nullptr;

	//ウィンドウクラスの設定
	WNDCLASS wc{};

};

