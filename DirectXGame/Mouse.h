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

	WindowsApp* windowsApp = nullptr;

	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	//�}�E�X�̍��W
	myMath::Vector2 mousePos;

public:

	//����������(���i�g��Ȃ�)
	void Initialize(IDirectInput8* directInput);
	//�X�V����(���i�g��Ȃ�)
	void Update();

	/// <summary>
	/// button�Ŏw�肵���{�^�����������u��
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool TriggerPush(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă����
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool KeepPush(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���𗣂����u��
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool TriggerRelease(MouseButton button);

	/// <summary>
	/// button�Ŏw�肵���{�^���������Ă��Ȃ���
	/// </summary>
	/// <param name="button">LEFT,RIGHT,CENTER�̂ǂꂩ</param>
	/// <returns></returns>
	bool KeepRelease(MouseButton button);

	//�}�E�X�̍��W�擾
	myMath::Vector2 GetmousePos();

	//�V���O���g��
	static Mouse* GetInstance();

private:

	Mouse() = default;
	~Mouse() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Mouse& operator=(const Mouse&) = delete;
	Mouse(const Mouse&) = delete;
};