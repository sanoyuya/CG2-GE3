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

#pragma region	�L�[�{�[�h

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

	/// <summary>
	/// button�Ŏw�肵���{�^�����������u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ControllerButtonTriggerPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă����
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ControllerButtonKeepPush(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���𗣂����u��
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ControllerButtonTriggerRelease(ControllerButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă��Ȃ���
	/// </summary>
	/// <param name="button">A��LB��</param>
	/// <returns></returns>
	bool ControllerButtonKeepRelease(ControllerButton button);

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|�����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool ControllerStickTriggerPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă����
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool ControllerStickKeepPush(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵����������߂����u��
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool ControllerStickTriggerRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// stick�Ŏw�肵�������ɓ|���Ă��Ȃ���
	/// </summary>
	/// <param name="stick">���X�e�B�b�N�Ȃ�L_�Z�Z,�E�X�e�B�b�N�Ȃ�R_�Z�Z</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns></returns>
	bool ControllerStickKeepRelease(ControllerStick stick, const float& deadRange = 0.3f, const myMath::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �Q�[���p�b�h�̐U��
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void ShakeController(const float& power, const int& span);

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

#pragma endregion

	//�V���O���g��
	static InputManager* GetInstance();

private:

	InputManager() = default;
	~InputManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	InputManager& operator=(const InputManager&) = delete;
	InputManager(const InputManager&) = delete;
};