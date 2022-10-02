#include "Mouse.h"
#include <algorithm>

void Mouse::Initialize(IDirectInput8* directInput)
{
	HRESULT result;

	//クラス読み込み
	windowsApp = WindowsApp::GetInstance();

	//マウスデバイスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = mouse->SetDataFormat(&c_dfDIMouse2);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = mouse->SetCooperativeLevel(windowsApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Mouse::Update()
{
	//マウス情報の取得開始
	mouse->Acquire();
	oldMouseState = mouseState;
	mouse->GetDeviceState(sizeof(mouseState), &mouseState);

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindowA("DirectXGame", nullptr), &point);
	mousePos.x = static_cast<float>(point.x);
	mousePos.x = std::clamp(mousePos.x, 0.0f, static_cast<float>(WindowsApp::GetInstance()->GetWidth()));
	mousePos.y = static_cast<float>(point.y);
	mousePos.y = std::clamp(mousePos.y, 0.0f, static_cast<float>(WindowsApp::GetInstance()->GetHeight()));
}

bool Mouse::TriggerPush(MouseButton button)
{
	return (mouseState.rgbButtons[button] && !oldMouseState.rgbButtons[button]);
}

bool Mouse::KeepPush(MouseButton button)
{
	return static_cast<bool>(mouseState.rgbButtons[button]);
}

bool Mouse::TriggerRelease(MouseButton button)
{
	return (!mouseState.rgbButtons[button] && oldMouseState.rgbButtons[button]);
}

bool Mouse::KeepRelease(MouseButton button)
{
	return static_cast<bool>(!mouseState.rgbButtons[button]);
}

myMath::Vector2 Mouse::GetmousePos()
{
	return mousePos;
}

Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}