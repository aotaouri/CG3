#include "WinApp.h"

#ifdef USE_IMGUI
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif

//ウインドウプロシージャ
LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
#ifdef USE_IMGUI
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}
#endif

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
		//ウインドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize()
{
	//ウインドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	//ウインドウクラス名
	wc_.lpszClassName = L"CG3WindowClass";
	//インスタントハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウインドウクラスを登録する
	RegisterClass(&wc_);

	//ウインドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウインドウの生成
	hwnd_ = CreateWindow(
		wc_.lpszClassName,       // 利用するクラス名
		L"LE2C_01_アオタ_オウリ", // タイトルバーの文字
		WS_OVERLAPPEDWINDOW,     // よく見るウインドウスタイル
		CW_USEDEFAULT,           // 表示X座標
		CW_USEDEFAULT,           // 表示Y座標
		wrc.right - wrc.left,    // ウインドウ横幅
		wrc.bottom - wrc.top,    // ウインドウ縦幅
		nullptr,                 // 親ウインドウハンドル
		nullptr,                 // メニューハンドル
		wc_.hInstance,           // インスタントハンドル
		nullptr);                // オプション
}

void WinApp::Finalize()
{
	CloseWindow(hwnd_);
}