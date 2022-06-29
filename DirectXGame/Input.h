#pragma once
#include<dinput.h>
#include<DirectXMath.h>
using namespace DirectX;
class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};

	HRESULT result;

public:
	void Initialize(HWND hwnd, WNDCLASSEX w);
	void Update();

	bool TriggerPush(int keyName);
	bool KeepPush(int keyName);
	bool TriggerRelease(int keyName);
	bool KeepRelease(int keyName);
};

