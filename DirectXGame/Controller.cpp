#include "Controller.h"

bool Controller::StickInDeadZone(myMath::Vector2& thumb, const myMath::Vector2& deadRate)
{
	bool x = false;
	bool y = false;

	if ((thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.x && thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.x)) {
		thumb.x = 0.0f;
		x = true;
	}
	if ((thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.y && thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.y)) {
		thumb.y = 0.0f;
		y = true;
	}

	if (x && y) {
		return true;
	}

	return false;
}

void Controller::Update()
{
	oldControllerState = controllerState;
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	//�R���g���[���[�擾
	DWORD dwResult = XInputGetState(0, &controllerState);

	if (dwResult == ERROR_SUCCESS) {
		//�R���g���[���[���ڑ�����Ă���
		if (0 < shakeTimer) {
			shakeTimer--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer == 0) {
				vibration.wLeftMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
			}
			else {
				vibration.wLeftMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
			}

			XInputSetState(dwResult, &vibration);
		}
	}
	else {
		//�R���g���[���[���ڑ�����Ă��Ȃ�
	}
}

bool Controller::ButtonTriggerPush(ControllerButton button)
{
	//�g���K�[
	if (button == LT) {
		return oldControllerState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonKeepPush(button);
	}
	else if (button == RT) {
		return oldControllerState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonKeepPush(button);
	}
	else {
		return !(oldControllerState.Gamepad.wButtons & button) && ButtonKeepPush(button);
	}
}

bool Controller::ButtonKeepPush(ControllerButton button)
{
	if (button == LT) {
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < controllerState.Gamepad.bLeftTrigger;
	}
	else if (button == RT) {
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < controllerState.Gamepad.bRightTrigger;
	}
	else {
		return controllerState.Gamepad.wButtons & button;
	}
}

bool Controller::ButtonTriggerRelease(ControllerButton button)
{
	//�g���K�[
	if (button == LT) {
		return oldControllerState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonKeepPush(button);
	}
	else if (button == RT) {
		return oldControllerState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonKeepPush(button);
	}
	else {
		return oldControllerState.Gamepad.wButtons & button && !ButtonKeepPush(button);
	}
}

bool Controller::ButtonKeepRelease(ControllerButton button)
{
	if (button == LT) {
		return !XINPUT_GAMEPAD_TRIGGER_THRESHOLD < controllerState.Gamepad.bLeftTrigger;
	}
	else if (button == RT) {
		return !XINPUT_GAMEPAD_TRIGGER_THRESHOLD < controllerState.Gamepad.bRightTrigger;
	}
	else {
		return !(controllerState.Gamepad.wButtons & button);
	}
}

bool Controller::StickTriggerPush(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = stick <= L_RIGHT;
	if (isLeftStick) {
		oldVec = myMath::Vector2(oldControllerState.Gamepad.sThumbLX, oldControllerState.Gamepad.sThumbLY);
		vec = myMath::Vector2(controllerState.Gamepad.sThumbLX, controllerState.Gamepad.sThumbLY);
	}
	else {
		oldVec = myMath::Vector2(oldControllerState.Gamepad.sThumbRX, oldControllerState.Gamepad.sThumbRY);
		vec = myMath::Vector2(controllerState.Gamepad.sThumbRX, controllerState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate)) {
		return false;
	}

	if (StickInDeadZone(vec, deadRate)) {
		return false;
	}

	bool result = false;

	if (stick % 4 == L_UP) {
		result = !(deadRange < (oldVec.y / STICK_INPUT_MAX)) && deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stick % 4 == L_DOWN) {
		result = !(oldVec.y / STICK_INPUT_MAX < -deadRange) && vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stick % 4 == L_RIGHT) {
		result = !(deadRange < (oldVec.x / STICK_INPUT_MAX)) && deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stick % 4 == L_LEFT) {
		result = !(oldVec.x / STICK_INPUT_MAX < -deadRange) && vec.x / STICK_INPUT_MAX < -deadRange;
	}
	else {
		assert(0);
	}

	return result;
}

bool Controller::StickKeepPush(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	myMath::Vector2 vec;
	bool isLeftStick = stick <= L_RIGHT;

	if (isLeftStick) {
		vec = myMath::Vector2(controllerState.Gamepad.sThumbLX, controllerState.Gamepad.sThumbLY);
	}
	else {
		vec = myMath::Vector2(controllerState.Gamepad.sThumbRX, controllerState.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, deadRate))return false;

	if (stick % 4 == L_UP) {
		return deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stick % 4 == L_DOWN) {
		return  vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stick % 4 == L_RIGHT) {
		return deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stick % 4 == L_LEFT) {
		return  vec.x / STICK_INPUT_MAX < -deadRange;
	}

	assert(0);
	return false;
}

bool Controller::StickTriggerRelease(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = stick <= L_RIGHT;

	if (isLeftStick) {
		oldVec = myMath::Vector2(oldControllerState.Gamepad.sThumbLX, oldControllerState.Gamepad.sThumbLY);
		vec = myMath::Vector2(controllerState.Gamepad.sThumbLX, controllerState.Gamepad.sThumbLY);
	}
	else {
		oldVec = myMath::Vector2(oldControllerState.Gamepad.sThumbRX, oldControllerState.Gamepad.sThumbRY);
		vec = myMath::Vector2(controllerState.Gamepad.sThumbRX, controllerState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate)) {
		return false;
	}

	if (StickInDeadZone(vec, deadRate)) {
		return false;
	}

	bool result = false;

	if (stick % 4 == L_UP) {
		result = deadRange < (oldVec.y / STICK_INPUT_MAX) && !(deadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (stick % 4 == L_DOWN) {
		result = oldVec.y / STICK_INPUT_MAX < -deadRange && !(vec.y / STICK_INPUT_MAX < -deadRange);
	}
	else if (stick % 4 == L_RIGHT) {
		result = deadRange < (oldVec.x / STICK_INPUT_MAX) && !(deadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (stick % 4 == L_LEFT) {
		result = oldVec.x / STICK_INPUT_MAX < -deadRange && !(vec.x / STICK_INPUT_MAX < -deadRange);
	}
	else {
		assert(0);
	}

	return result;
}

bool Controller::StickKeepRelease(ControllerStick stick, const float& deadRange, const myMath::Vector2& deadRate)
{
	return !StickKeepPush(stick, deadRange, deadRate);
}

void Controller::ShakeController(const float& power, const int& span)
{
	if (!(0 < power && power <= 1.0f)) {
		assert(0);
	}

	shakePower = power;
	shakeTimer = span;
}

myMath::Vector2 Controller::GetLeftStickVec(const myMath::Vector2& deadRate)
{
	myMath::Vector2 result(static_cast<float>(controllerState.Gamepad.sThumbLX), static_cast<float>(-controllerState.Gamepad.sThumbLY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

myMath::Vector2 Controller::GetRightStickVec(const myMath::Vector2& deadRate)
{
	myMath::Vector2 result(static_cast<float>(controllerState.Gamepad.sThumbRX), static_cast<float>(-controllerState.Gamepad.sThumbRY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;;
}

Controller* Controller::GetInstance()
{
	static Controller instance;
	return &instance;
}