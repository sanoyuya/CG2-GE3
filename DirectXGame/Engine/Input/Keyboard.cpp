#include "Keyboard.h"
#include <cassert>

void Keyboard::Initialize(IDirectInput8* directInput,WindowsApp* windowsApp)
{
	HRESULT result;

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard_->SetCooperativeLevel(windowsApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Keyboard::Update()
{
	for (int i = 0; i < _countof(oldkey_); i++) {
		oldkey_[i] = key_[i];
	}
	//キーボード情報の取得開始
	keyboard_->Acquire();
	keyboard_->GetDeviceState(sizeof(key_), key_);
}

bool Keyboard::TriggerPush(int keyName)
{
	return key_[keyName] && !oldkey_[keyName];
}

bool Keyboard::KeepPush(int keyName)
{
	return key_[keyName];
}

bool Keyboard::TriggerRelease(int keyName)
{
	return !key_[keyName] && oldkey_[keyName];
}

bool Keyboard::KeepRelease(int keyName)
{
	return !key_[keyName] && !oldkey_[keyName];
}

Keyboard* Keyboard::GetInstance()
{
	static Keyboard instance;
	return &instance;
}