
#include "Controller.h"
//#include<winnt.h>
#pragma comment(lib,"xinput.lib")

#define STICK_INPUT_MAX 32768.0f

void Controller::Initialize() {

}

void Controller::Update() {
	//コントローラー
	oldXinputState = xinputState;
	ZeroMemory(&xinputState, sizeof(XINPUT_STATE));

	//コントローラー取得
	DWORD dwResult = XInputGetState(0, &xinputState);

	if (dwResult == ERROR_SUCCESS) {
		//コントローラーが接続されている
		if (0 < shakeTimer) {
			shakeTimer--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer == 0) {
				vibration.wLeftMotorSpeed = 0.0f; // use any value between 0-65535 here
				vibration.wRightMotorSpeed = 0.0f; // use any value between 0-65535 here
			}
			else {
				vibration.wLeftMotorSpeed = 65535.0f * shakePower; // use any value between 0-65535 here
				vibration.wRightMotorSpeed = 65535.0f * shakePower; // use any value between 0-65535 here
			}
			XInputSetState(dwResult, &vibration);
		}
	}
	else {
		//コントローラーが接続されていない
	}
}

bool Controller::StickInDeadZone(myMath::Vector2& Thumb, const myMath::Vector2& DeadRate){
	bool x = false, y = false;
	if ((Thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x
		&& Thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x))
	{
		Thumb.x = 0.0f;
		x = true;
	}
	if ((Thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y
		&& Thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y))
	{
		Thumb.y = 0.0f;
		y = true;
	}
	if (x && y)return true;
	return false;
}

bool Controller::OnTrigger(CONTROLLER Button)
{
	//トリガー
	if (Button == LT)
	{
		return oldXinputState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD
			&& Input(Button);
	}
	else if (Button == RT)
	{
		return oldXinputState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD
			&& Input(Button);
	}
	else
	{
		return !(oldXinputState.Gamepad.wButtons & Button)
			&& Input(Button);
	}
	assert(0);
	return false;
}

bool Controller::OnTrigger(CONTROLLER StickInput, const float& DeadRange, const myMath::Vector2& DeadRate)
{
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = StickInput <= L_RIGHT;
	if (isLeftStick)
	{
		oldVec = myMath::Vector2 (oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = myMath::Vector2 (oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, DeadRate))return false;
	if (StickInDeadZone(vec, DeadRate))return false;

	bool result = false;

	if (StickInput % 4 == L_UP)
	{
		result = !(DeadRange < (oldVec.y / STICK_INPUT_MAX))
			&& DeadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (StickInput % 4 == L_DOWN)
	{
		result = !(oldVec.y / STICK_INPUT_MAX < -DeadRange)
			&& vec.y / STICK_INPUT_MAX < -DeadRange;
	}
	else if (StickInput % 4 == L_RIGHT)
	{
		result = !(DeadRange < (oldVec.x / STICK_INPUT_MAX))
			&& DeadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (StickInput % 4 == L_LEFT)
	{
		result = !(oldVec.x / STICK_INPUT_MAX < -DeadRange)
			&& vec.x / STICK_INPUT_MAX < -DeadRange;
	}
	else
	{
		assert(0);
	}

	return result;
}

bool Controller::Input(CONTROLLER Button)
{
	if (Button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bLeftTrigger;
	}
	else if (Button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bRightTrigger;
	}
	else
	{
		return xinputState.Gamepad.wButtons & Button;
	}
	assert(0);
	return false;
}

bool Controller::Input(CONTROLLER_STICK StickInput, const float& DeadRange, const myMath::Vector2& DeadRate)
{
	myMath::Vector2 vec;
	bool isLeftStick = StickInput <= L_RIGHT;
	if (isLeftStick)
	{
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, DeadRate))return false;

	if (StickInput % 4 == L_UP)
	{
		return DeadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (StickInput % 4 == L_DOWN)
	{
		return  vec.y / STICK_INPUT_MAX < -DeadRange;
	}
	else if (StickInput % 4 == L_RIGHT)
	{
		return DeadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (StickInput % 4 == L_LEFT)
	{
		return  vec.x / STICK_INPUT_MAX < -DeadRange;
	}

	assert(0);
	return false;
}

bool Controller::OffTrigger(CONTROLLER Button)
{
	//トリガー
	if (Button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bLeftTrigger
			&& !Input(Button);
	}
	else if (Button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bRightTrigger
			&& !Input(Button);
	}
	//ボタン
	else
	{
		return (oldXinputState.Gamepad.wButtons & Button)
			&& !Input(Button);
	}
	assert(0);
	return false;
}

bool Controller::OffTrigger(CONTROLLER_STICK StickInput, const float& DeadRange, const myMath::Vector2& DeadRate)
{
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = StickInput <= L_RIGHT;
	if (isLeftStick)
	{
		oldVec = myMath::Vector2 (oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = myMath::Vector2 (oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = myMath::Vector2 (xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, DeadRate))return false;
	if (StickInDeadZone(vec, DeadRate))return false;

	bool result = false;
	if (StickInput % 4 == L_UP)
	{
		result = DeadRange < (oldVec.y / STICK_INPUT_MAX)
			&& !(DeadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (StickInput % 4 == L_DOWN)
	{
		result = oldVec.y / STICK_INPUT_MAX < -DeadRange
			&& !(vec.y / STICK_INPUT_MAX < -DeadRange);
	}
	else if (StickInput % 4 == L_RIGHT)
	{
		result = DeadRange < (oldVec.x / STICK_INPUT_MAX)
			&& !(DeadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (StickInput % 4 == L_LEFT)
	{
		result = oldVec.x / STICK_INPUT_MAX < -DeadRange
			&& !(vec.x / STICK_INPUT_MAX < -DeadRange);
	}
	else
	{
		assert(0);
	}
	if (result)
	{
	}
	return result;
}

myMath::Vector2 Controller::GetLeftStickVec(const myMath::Vector2& DeadRate)
{
	myMath::Vector2 result(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	StickInDeadZone(result, DeadRate);
	return result.normalization();
}

myMath::Vector2 Controller::GetRightStickVec(const myMath::Vector2& DeadRate)
{
	myMath::Vector2 result(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	StickInDeadZone(result, DeadRate);
	return result.normalization();
}

void Controller::ShakeController(const float& Power, const int& Span)
{
	if (!(0 < Power && Power <= 1.0f))assert(0);
	shakePower = Power;
	shakeTimer = Span;
}
