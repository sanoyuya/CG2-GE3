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

	//�L�[�{�[�h
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};

	//�}�E�X
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	//�}�E�X�̍��W
	myMath::Vector2 mousePos;

	//�Q�[���p�b�h
	Microsoft::WRL::ComPtr<IDirectInputDevice8> joyPad = nullptr;
	XINPUT_STATE padState{};
	XINPUT_STATE oldPadState{};
	//�R���g���[���[�U������
	float shakePower = 0.0f;
	//�R���g���[���[�U������(�t���[����)
	int shakeTimer = 0;

	//�f�b�h�]�[���ɓ����Ă��邩(DeadRate : �f�b�h�]�[������̓x�����A1.0f���ƃf�t�H���g)
	bool StickInDeadZone(myMath::Vector2& thumb, const myMath::Vector2& deadRate);

	//�ō����͋��x
	const float STICK_INPUT_MAX = 32768.0f;

public:
	Input();
	~Input();
	void Initialize();
	void Update();

#pragma region	�L�[�{�[�h

	void KeyboardInitialize();
	void KeyboardUpdate();
	bool KeyboardTriggerPush(int keyName);
	bool KeyboardKeepPush(int keyName);
	bool KeyboardTriggerRelease(int keyName);
	bool KeyboardKeepRelease(int keyName);

#pragma endregion

#pragma region �}�E�X

	void MouseInitialize();
	void MouseUpdate();
	bool MouseTriggerPush(MouseButton button);
	bool MouseKeepPush(MouseButton button);
	bool MouseTriggerRelease(MouseButton button);
	bool MouseKeepRelease(MouseButton button);
	myMath::Vector2 GetmousePos();

#pragma endregion

#pragma region	�Q�[���p�b�h

	void JoyPadUpdate();
	bool JoyPadButtonTriggerPush(ControllerButton button);
	bool JoyPadButtonKeepPush(ControllerButton button);
	bool JoyPadButtonTriggerRelease(ControllerButton button);
	bool JoyPadButtonKeepRelease(ControllerButton button);
	bool JoyPadStickTriggerPush(ControllerStick stickInput, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });
	bool JoyPadStickKeepPush(ControllerStick stickInput, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });
	bool JoyPadStickTriggerRelease(ControllerStick stickInput, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });
	bool JoyPadStickKeepRelease(ControllerStick stickInput, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	void ShakeController(const float& power, const int& span);

#pragma endregion

	//�Q�b�^�[
	static Input* GetInstance();
};

