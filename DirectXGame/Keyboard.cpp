#include "Keyboard.h"
#include <cassert>

void Keyboard::Initialize(IDirectInput8* directInput)
{
	HRESULT result;

	//クラス読み込み
	windowsApp = WindowsApp::GetInstance();

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(windowsApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Keyboard::Update()
{
	for (int i = 0; i < _countof(oldkey); i++) {
		oldkey[i] = key[i];
	}
	//キーボード情報の取得開始
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Keyboard::TriggerPush(int keyName)
{
	return key[keyName] && !oldkey[keyName];
}

bool Keyboard::KeepPush(int keyName)
{
	return key[keyName];
}

bool Keyboard::TriggerRelease(int keyName)
{
	return !key[keyName] && oldkey[keyName];
}

bool Keyboard::KeepRelease(int keyName)
{
	return !key[keyName] && !oldkey[keyName];
}

Keyboard* Keyboard::GetInstance()
{
	static Keyboard instance;
	return &instance;
}