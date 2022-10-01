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
	//�S�̂̏���������
	void Initialize();
	//�S�̂̍X�V����
	void Update();

#pragma region	�L�[�{�[�h

	//����������(���i�g��Ȃ�)
	void KeyboardInitialize();
	//�X�V����(���i�g��Ȃ�)
	void KeyboardUpdate();

	/// <summary>
	/// keyName�Ŏw�肵���L�[���������u��
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeyboardTriggerPush(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�������Ă����
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeyboardKeepPush(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�𗣂����u��
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeyboardTriggerRelease(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�������Ă��Ȃ���
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeyboardKeepRelease(int keyName);

#pragma endregion

#pragma region �}�E�X

	//����������(���i�g��Ȃ�)
	void MouseInitialize();
	//�X�V����(���i�g��Ȃ�)
	void MouseUpdate();

	/// <summary>
	/// button�Ŏw�肵���{�^�����������u��
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool MouseTriggerPush(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă����
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool MouseKeepPush(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���𗣂����u��
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool MouseTriggerRelease(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă��Ȃ���
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool MouseKeepRelease(MouseButton button);

	//�}�E�X�̍��W�擾
	myMath::Vector2 GetmousePos();

#pragma endregion

#pragma region	�Q�[���p�b�h

	//�X�V����(���i�g��Ȃ�)
	void JoyPadUpdate();

	/// <summary>
	/// button�Ŏw�肵���{�^�����������u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool JoyPadButtonTriggerPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă����
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool JoyPadButtonKeepPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���𗣂����u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool JoyPadButtonTriggerRelease(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă��Ȃ���
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool JoyPadButtonKeepRelease(ControllerButton button);

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|�����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickTriggerPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă����
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickKeepPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵����������߂����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickTriggerRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă��Ȃ���
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange"></param>
	/// <param name="deadRate"></param>
	/// <returns></returns>
	bool JoyPadStickKeepRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	//L�X�e�B�b�N�̌X���̎擾
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	//R�X�e�B�b�N�̌X���̎擾
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
	//�Q�[���p�b�h�̐U��
	void ShakeController(const float& power, const int& span);

#pragma endregion

	//�V���O���g��
	static Input* GetInstance();
};

