#pragma once
#include <Windows.h>
#include <cstdint>

// ウィンドウアプリケーション
class WinApp
{
public:
	// クライアント領域のサイズ(クラスの定数)
	static constexpr int32_t kClientWidth = 1280;
	static constexpr int32_t kClientHeight = 720;


	// ウィンドウプロシージャ(静的メンバ関数)
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


	// 初期化(ウィンドウクラスの登録とウィンドウの生成)
	void Initialize();
	// 終了
	void Finalize();

	// getter
	HWND GetHwnd() const { return hwnd_; }
	HINSTANCE GetHInstance() const { return wc_.hInstance; }

private:
	// ウィンドウハンドル
	HWND hwnd_ = nullptr;
	// ウィンドウクラスの設定
	WNDCLASS wc_{};
};