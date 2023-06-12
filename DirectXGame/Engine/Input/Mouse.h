#pragma once
#include<dinput.h>
#include<wrl.h>
#include "myMath.h"
#include"WindowsApp.h"

enum MouseButton
{
	LEFT,
	RIGHT,
	CENTER
};

class Mouse
{
private:

	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse_ = nullptr;
	DIMOUSESTATE2 mouseState_ = {};
	DIMOUSESTATE2 oldMouseState_ = {};
	//マウスの座標
	myMath::Vector2 mousePos_;

	float width_ = 0.0f;
	float height_ = 0.0f;

public:

	//初期化処理(普段使わない)
	void Initialize(IDirectInput8* directInput, WindowsApp* windowsApp);
	//更新処理(普段使わない)
	void Update();

	/// <summary>
	/// buttonで指定したボタンを押した瞬間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool TriggerPush(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを押している間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool KeepPush(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを離した瞬間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool TriggerRelease(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを押していない間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool KeepRelease(MouseButton button);

	//マウスの座標取得
	myMath::Vector2 GetmousePos();
};