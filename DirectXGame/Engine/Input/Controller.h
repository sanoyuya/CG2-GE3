#pragma once
#include<dinput.h>
#include<DirectXMath.h>
#include<wrl.h>
#include "myMath.h"
#include <xinput.h>
#pragma comment (lib, "xinput.lib")

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

class Controller
{
private:

	Microsoft::WRL::ComPtr<IDirectInputDevice8> controller_ = nullptr;
	XINPUT_STATE controllerState_{};
	XINPUT_STATE oldControllerState_{};
	//�R���g���[���[�U������
	float shakePower_ = 0.0f;
	//�R���g���[���[�U������(�t���[����)
	float shakeTimer_ = 0.0f;

	//�f�b�h�]�[���ɓ����Ă��邩(DeadRate : �f�b�h�]�[������̓x�����A1.0f���ƃf�t�H���g)
	bool StickInDeadZone(myMath::Vector2& thumb, const myMath::Vector2& deadRate);

	//�ō����͋��x
	const float STICK_INPUT_MAX_ = 32768.0f;

public:

	//�X�V����(���i�g��Ȃ�)
	void Update();

	/// <summary>
	/// button�Ŏw�肵���{�^�����������u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ButtonTriggerPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă����
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ButtonKeepPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���𗣂����u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ButtonTriggerRelease(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă��Ȃ���
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ButtonKeepRelease(ControllerButton button);

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|�����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool StickTriggerPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă����
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool StickKeepPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵����������߂����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool StickTriggerRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă��Ȃ���
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool StickKeepRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �Q�[���p�b�h�̐U��
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void ShakeController(const float& power, const float& span);

	/// <summary>
	/// L�X�e�B�b�N�̌X���̎擾
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// R�X�e�B�b�N�̌X���̎擾
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& deadRate = { 1.0f,1.0f });
};