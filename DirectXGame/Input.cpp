#include "Input.h"
//#define DIRECTINPUT_VERSION 0x0800	//DirectInputのバージョン指定
#include<dinput.h>
#include<DirectXMath.h>
using namespace DirectX;

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::KeyboardInitialize(HWND hwnd, WNDCLASSEX w){//初期化
	//DirectInputの初期化
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	
	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::KeyboardUpdate() {//更新処理
	for (int i = 0; i < _countof(oldkey); i++) {
		oldkey[i] = key[i];
	}
	//キーボード情報の取得開始
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

void Input::MouseInitialize(HWND hwnd, WNDCLASSEX w){
	//DirectInputの初期化
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//マウスデバイスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));


	//入力データ形式のセット
	result = mouse->SetDataFormat(&c_dfDIMouse2);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::MouseUpdate(){
	for (int i = 0; i < _countof(oldkey); i++) {
		oldkey[i] = key[i];
	}
	//マウス情報の取得開始
	mouse->Acquire();
	mouse->GetDeviceState(sizeof(key), key);
}

void Input::JoyPadInitialize()
{
}

void Input::JoyPadUpdate()
{
}

bool Input::KeyboardTriggerPush(int keyName) {//押した瞬間
	return key[keyName] && !oldkey[keyName];
}

bool Input::KeyboardKeepPush(int keyName) {//押されている間
	return key[keyName];
}

bool Input::KeyboardTriggerRelease(int keyName) {//離された瞬間
	return !key[keyName] && oldkey[keyName];
}

bool Input::KeyboardKeepRelease(int keyName) {//離している間
	return !key[keyName]&&!oldkey[keyName];
}

bool Input::MouseTriggerPush(int keyName)//押した瞬間
{
	return key[keyName] && !oldkey[keyName];
}

bool Input::MouseKeepPush(int keyName)//押されている間
{
	return key[keyName];
}

bool Input::MouseTriggerRelease(int keyName)//離された瞬間
{
	return !key[keyName] && oldkey[keyName];
}

bool Input::MouseKeepRelease(int keyName)//離している間
{
	return !key[keyName] && !oldkey[keyName];
}
