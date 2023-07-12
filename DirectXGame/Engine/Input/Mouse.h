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
	//�}�E�X�̍��W
	myMath::Vector2 mousePos_;

	float width_ = 0.0f;
	float height_ = 0.0f;

public:

	//����������(���i�g��Ȃ�)
	void Initialize(IDirectInput8* directInput, WindowsApp* windowsApp);
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
};