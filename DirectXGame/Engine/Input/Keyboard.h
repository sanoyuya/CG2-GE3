#pragma once
#include<dinput.h>
#include<wrl.h>
#include"WindowsApp.h"

class Keyboard
{
private:

	//キーボード
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard_ = nullptr;
	BYTE oldkey_[256] = {};
	BYTE key_[256] = {};

public:

	//初期化処理(普段使わない)
	void Initialize(IDirectInput8* directInput, WindowsApp* windowsApp);
	//更新処理(普段使わない)
	void Update();

	/// <summary>
	/// keyNameで指定したキーを押した瞬間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool TriggerPush(int keyName);

	/// <summary>
	/// keyNameで指定したキーを押している間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeepPush(int keyName);

	/// <summary>
	/// keyNameで指定したキーを離した瞬間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool TriggerRelease(int keyName);

	/// <summary>
	/// keyNameで指定したキーを押していない間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeepRelease(int keyName);
};