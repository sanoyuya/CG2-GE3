#include "Mouse.h"
#include <algorithm>

void Mouse::Initialize(IDirectInput8* directInput, WindowsApp* windowsApp)
{
	HRESULT result;

	width_ = windowsApp->GetWidth();
	height_ = windowsApp->GetHeight();

	//�}�E�X�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysMouse, &mouse_, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = mouse_->SetDataFormat(&c_dfDIMouse2);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = mouse_->SetCooperativeLevel(windowsApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Mouse::Update()
{
	//�}�E�X���̎擾�J�n
	mouse_->Acquire();
	oldMouseState_ = mouseState_;
	mouse_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindowA("DirectXGame", nullptr), &point);
	mousePos_.x = static_cast<float>(point.x);
	mousePos_.x = std::clamp(mousePos_.x, 0.0f, width_);
	mousePos_.y = static_cast<float>(point.y);
	mousePos_.y = std::clamp(mousePos_.y, 0.0f, height_);
}

bool Mouse::TriggerPush(MouseButton button)
{
	return (mouseState_.rgbButtons[button] && !oldMouseState_.rgbButtons[button]);
}

bool Mouse::KeepPush(MouseButton button)
{
	return static_cast<bool>(mouseState_.rgbButtons[button]);
}

bool Mouse::TriggerRelease(MouseButton button)
{
	return (!mouseState_.rgbButtons[button] && oldMouseState_.rgbButtons[button]);
}

bool Mouse::KeepRelease(MouseButton button)
{
	return static_cast<bool>(!mouseState_.rgbButtons[button]);
}

myMath::Vector2 Mouse::GetmousePos()
{
	return mousePos_;
}

Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}