#pragma once
#include<dinput.h>
#include<wrl.h>
#include"WindowsApp.h"

class Keyboard
{
private:

	//�L�[�{�[�h
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard_ = nullptr;
	BYTE oldkey_[256] = {};
	BYTE key_[256] = {};

public:

	//����������(���i�g��Ȃ�)
	void Initialize(IDirectInput8* directInput, WindowsApp* windowsApp);
	//�X�V����(���i�g��Ȃ�)
	void Update();

	/// <summary>
	/// keyName�Ŏw�肵���L�[���������u��
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool TriggerPush(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�������Ă����
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeepPush(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�𗣂����u��
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool TriggerRelease(int keyName);

	/// <summary>
	/// keyName�Ŏw�肵���L�[�������Ă��Ȃ���
	/// </summary>
	/// <param name="keyName">DIK_�Z�Z</param>
	/// <returns></returns>
	bool KeepRelease(int keyName);
};