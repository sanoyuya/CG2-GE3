#pragma once
#include<dinput.h>
#include<DirectXMath.h>
using namespace DirectX;
class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
	IDirectInputDevice8* mouse = nullptr;
	IDirectInputDevice8* joyPad = nullptr;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};

	HRESULT result;

public:
	void KeyboardInitialize(HWND hwnd, WNDCLASSEX w);
	void KeyboardUpdate();

	void MouseInitialize(HWND hwnd, WNDCLASSEX w);
	void MouseUpdate();

	void JoyPadInitialize();
	void JoyPadUpdate();

	bool KeyboardTriggerPush(int keyName);
	bool KeyboardKeepPush(int keyName);
	bool KeyboardTriggerRelease(int keyName);
	bool KeyboardKeepRelease(int keyName);

	bool MouseTriggerPush(int keyName);
	bool MouseKeepPush(int keyName);
	bool MouseTriggerRelease(int keyName);
	bool MouseKeepRelease(int keyName);
};

