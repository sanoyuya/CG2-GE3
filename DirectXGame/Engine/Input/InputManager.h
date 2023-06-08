#pragma once
#include"WindowsApp.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"Controller.h"

class InputManager
{
private:

	Keyboard* keyboard = nullptr;
	Mouse* mouse = nullptr;
	Controller* controller = nullptr;

	Microsoft::WRL::ComPtr<IDirectInput8> directInput = nullptr;

public:

	void Initialize(WindowsApp* windowsApp);
	void Update();

#pragma region	キーボード

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

	/// <summary>
	/// buttonで指定したボタンを押した瞬間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool ControllerButtonTriggerPush(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを押している間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool ControllerButtonKeepPush(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを離した瞬間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool ControllerButtonTriggerRelease(ControllerButton button);

	/// <summary>
	/// buttonで指定したボタンを押していない間
	/// </summary>
	/// <param name="button">AやLB等</param>
	/// <returns></returns>
	bool ControllerButtonKeepRelease(ControllerButton button);

	/// <summary>
	/// stickで指定した方向に倒した瞬間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange">デッドゾーンの範囲初期値0.3f</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	bool ControllerStickTriggerPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向に倒している間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange">デッドゾーンの範囲初期値0.3f</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	bool ControllerStickKeepPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向から戻した瞬間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange">デッドゾーンの範囲初期値0.3f</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	bool ControllerStickTriggerRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stickで指定した方向に倒していない間
	/// </summary>
	/// <param name="stick">左スティックならL_〇〇,右スティックならR_〇〇</param>
	/// <param name="deadRange">デッドゾーンの範囲初期値0.3f</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	bool ControllerStickKeepRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// ゲームパッドの振動
	/// </summary>
	/// <param name="power">振動の強さ0.0f～1.0f</param>
	/// <param name="span">振動の時間フレーム</param>
	void ShakeController(const float& power, const int& span);

	/// <summary>
	/// Lスティックの傾きの取得
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// Rスティックの傾きの取得
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns></returns>
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });

#pragma endregion

	//シングルトン
	static InputManager* GetInstance();

private:

	InputManager() = default;
	~InputManager() = default;

	//コピーコンストラクタ・代入演算子削除
	InputManager& operator=(const InputManager&) = delete;
	InputManager(const InputManager&) = delete;
};