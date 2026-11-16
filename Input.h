#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <Windows.h>
#include <dinput.h>
#include <wrl.h>

class WinApp; // 前方宣言(ヘッダーのインクルードは最小限にする)

// 入力
class Input
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	// 初期化
	void Initialize(WinApp* winApp);
	// 更新(毎フレーム、ゲーム処理の最初に呼ぶ)
	void Update();

	// キーの押下をチェック
	bool PushKey(BYTE keyNumber) const;
	// キーのトリガーをチェック(押した瞬間だけtrue)
	bool TriggerKey(BYTE keyNumber) const;

	// 全キーの現在の状態(DebugCamera::Update(key) などに渡す用)
	BYTE* GetKeys() { return key_; }

private:
	// DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput_;
	// キーボードデバイス
	ComPtr<IDirectInputDevice8> keyboard_;
	// 全キーの状態
	BYTE key_[256] = {};
	// 前回の全キーの状態
	BYTE keyPre_[256] = {};
};