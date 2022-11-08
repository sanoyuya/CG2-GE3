#include "InputManager.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void InputManager::Initialize()
{
	HRESULT result;

	//�N���X�ǂݍ���
	windowsApp = WindowsApp::GetInstance();
	keyboard = Keyboard::GetInstance();
	mouse = Mouse::GetInstance();
	controller = Controller::GetInstance();

	//DirectInput�̏�����
	result = DirectInput8Create(windowsApp->GetW().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	keyboard->Initialize(directInput.Get());//�L�[�{�[�h����������
	mouse->Initialize(directInput.Get());//�}�E�X����������
}

void InputManager::Update()
{
	keyboard->Update();//�L�[�{�[�h�̍X�V����
	mouse->Update();//�}�E�X�̍X�V����
	controller->Update();//�R���g���[���[�̍X�V����
}

bool InputManager::KeyboardTriggerPush(int keyName)
{
	return keyboard->TriggerPush(keyName);
}

bool InputManager::KeyboardKeepPush(int keyName)
{
	return keyboard->KeepPush(keyName);
}

bool InputManager::KeyboardTriggerRelease(int keyName)
{
	return keyboard->TriggerRelease(keyName);
}

bool InputManager::KeyboardKeepRelease(int keyName)
{
	return keyboard->KeepRelease(keyName);
}

bool InputManager::MouseTriggerPush(MouseButton button)
{
	return mouse->TriggerPush(button);
}

bool InputManager::MouseKeepPush(MouseButton button)
{
	return mouse->KeepPush(button);
}

bool InputManager::MouseTriggerRelease(MouseButton button)
{
	return mouse->TriggerRelease(button);
}

bool InputManager::MouseKeepRelease(MouseButton button)
{
	return mouse->KeepRelease(button);
}

myMath::Vector2 InputManager::GetmousePos()
{
	return mouse->GetmousePos();
}

bool InputManager::ControllerButtonTriggerPush(ControllerButton button)
{
	return controller->ButtonTriggerPush(button);
}

bool InputManager::ControllerButtonKeepPush(ControllerButton button)
{
	return controller->ButtonKeepPush(button);
}

bool InputManager::ControllerButtonTriggerRelease(ControllerButton button)
{
	return controller->ButtonTriggerRelease(button);
}

bool InputManager::ControllerButtonKeepRelease(ControllerButton button)
{
	return controller->ButtonKeepRelease(button);
}

bool InputManager::ControllerStickTriggerPush(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	return controller->StickTriggerPush(stick, deadRange, deadRate);
}

bool InputManager::ControllerStickKeepPush(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	return controller->StickKeepPush(stick, deadRange, deadRate);
}

bool InputManager::ControllerStickTriggerRelease(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	return controller->StickTriggerRelease(stick, deadRange, deadRate);
}

bool InputManager::ControllerStickKeepRelease(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	return controller->StickKeepRelease(stick, deadRange, deadRate);
}

void InputManager::ShakeController(const float& power, const int& span)
{
	controller->ShakeController(power, span);
}

myMath::Vector2 InputManager::GetLeftStickVec(const myMath::Vector2& deadRate)
{
	return controller->GetLeftStickVec(deadRate);
}

myMath::Vector2 InputManager::GetRightStickVec(const myMath::Vector2& deadRate)
{
	return controller->GetRightStickVec(deadRate);
}

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}