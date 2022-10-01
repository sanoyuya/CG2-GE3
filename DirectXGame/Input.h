#pragma once
#include<dinput.h>
#include<DirectXMath.h>
#include"WindowsApp.h"
#include<wrl.h>
#include "myMath.h"
#include <xinput.h>
#pragma comment (lib, "xinput.lib")
using namespace DirectX;

enum MouseButton
{
	LEFT,
	RIGHT,
	CENTER
};

enum ControllerButton
{
	B = XINPUT_GAMEPAD_B,
	A = XINPUT_GAMEPAD_A,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LT,
	RT
};

enum ControllerStick
{
	L_UP, L_DOWN, L_LEFT, L_RIGHT,
	R_UP, R_DOWN, R_LEFT, R_RIGHT, XBOX_STICK_NUM
};

class Input
{
private:

	WindowsApp* windowsApp = nullptr;

	Microsoft::WRL::ComPtr<IDirectInput8> directInput = nullptr;

	//キーボード
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};

	//マウス
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	//マウスの座標
	myMath::Vector2 mousePos;

	//ゲームパッド
	Microsoft::WRL::ComPtr<IDirectInputDevice8> joyPad = nullptr;
	XINPUT_STATE padState{};
	XINPUT_STATE oldPadState{};
	//コントローラー振動強さ
	float shakePower = 0.0f;
	//コントローラー振動長さ(フレーム数)
	int shakeTimer = 0;

	//デッドゾーンに入っているか(DeadRate : デッドゾーン判定の度合い、1.0fだとデフォルト)
	bool StickInDeadZone(myMath::Vector2& thumb, const myMath::Vector2& deadRate);

	//最高入力強度
	const float STICK_INPUT_MAX = 32768.0f;

public:
	Input();
	~Input();
	//全体の初期化処理
	void Initialize();
	//全体の更新処理
	void Update();

#pragma region	キーボード

	//初期化処理(普段使わない)
	void KeyboardInitialize();
	//更新処理(普段使わない)
	void KeyboardUpdate();

	/// <summary>
	/// keyNameで指定したキーを押した瞬間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeyboardTriggerPush(int keyName);

	/// <summary>
	/// keyNameで指定したキーを押している間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeyboardKeepPush(int keyName);

	/// <summary>
	/// keyNameで指定したキーを離した瞬間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeyboardTriggerRelease(int keyName);

	/// <summary>
	/// keyNameで指定したキーを押していない間
	/// </summary>
	/// <param name="keyName">DIK_〇〇</param>
	/// <returns></returns>
	bool KeyboardKeepRelease(int keyName);

#pragma endregion

#pragma region マウス

	//初期化処理(普段使わない)
	void MouseInitialize();
	//更新処理(普段使わない)
	void MouseUpdate();

	/// <summary>
	/// buttonで指定したボタンを押した瞬間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool MouseTriggerPush(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを押している間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool MouseKeepPush(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを離した瞬間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool MouseTriggerRelease(MouseButton button);

	/// <summary>
	/// buttonで指定したボタンを押していない間
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTERのどれか</param>
	/// <returns></returns>
	bool MouseKeepRelease(MouseButton button);

	//マウスの座標取得
	myMath::Vector2 GetmousePos();

#pragma endregion

#pragma region	ゲームパッド

	//更新処理(普段使わない)
	void JoyPadUpdate();

	/// <summary>
	/// buttonで指定したボタンを押した瞬間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool JoyPadButtonTriggerPush(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを押している間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool JoyPadButtonKeepPush(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを離した瞬間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool JoyPadButtonTriggerRelease(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを押していない間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool JoyPadButtonKeepRelease(ControllerButton button);

	/// <summary>
	/// stickで指定した方向に倒した瞬間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickTriggerPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向に倒している間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickKeepPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向から戻した瞬間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickTriggerRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向に倒していない間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickKeepRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	//Lスティックの傾きの取得
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	//Rスティックの傾きの取得
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	//ゲームパッドの振動
	void ShakeController(const float& power, const int& span);

#pragma endregion

	//シングルトン
	static Input* GetInstance();
};

