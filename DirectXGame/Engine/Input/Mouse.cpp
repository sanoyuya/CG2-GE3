#include "Mouse.h"
#include <algorithm>

void Mouse::Initialize(IDirectInput8* directInput)
{
	HRESULT result;

	//�N���X�ǂݍ���
	windowsApp = WindowsApp::GetInstance();

	//�}�E�X�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = mouse->SetDataFormat(&c_dfDIMouse2);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = mouse->SetCooperativeLevel(windowsApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Mouse::Update()
{
	//�}�E�X���̎擾�J�n
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