#include "Input.h"
//#define DIRECTINPUT_VERSION 0x0800	//DirectInputのバージョン指定
#include<dinput.h>
#include<DirectXMath.h>
using namespace DirectX;

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <algorithm>

Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialize(){
	windowsApp = WindowsApp::GetInstance();

	HRESULT result;

	//DirectInputの初期化
	result = DirectInput8Create(windowsApp->GetW().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	KeyboardInitialize();//キーボード初期化処理
	MouseInitialize();//マウス初期化処理
}

void Input::Update(){
	KeyboardUpdate();//キーボード更新処理
	MouseUpdate();//マウス更新処理
	JoyPadUpdate();//ゲームパッド更新処理
}

#pragma region	キーボード

void Input::KeyboardInitialize() {//初期化
	HRESULT result;

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

void Input::KeyboardUpdate() {//更新処理
	for (int i = 0; i < _countof(oldkey); i++) {
		oldkey[i] = key[i];
	}
	//キーボード情報の取得開始
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
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

#pragma endregion

#pragma region	マウス

void Input::MouseInitialize() {
	HRESULT result;

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

void Input::MouseUpdate() {
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

bool Input::MouseTriggerPush(MouseButton button){//押した瞬間
	return (mouseState.rgbButtons[button]&& !oldMouseState.rgbButtons[button]);
}

bool Input::MouseKeepPush(MouseButton button){//押されている間
	return static_cast<bool>(mouseState.rgbButtons[button]);
}

bool Input::MouseTriggerRelease(MouseButton button){//離された瞬間
	return (!mouseState.rgbButtons[button]&& oldMouseState.rgbButtons[button]);
}

bool Input::MouseKeepRelease(MouseButton button){//離している間
	return static_cast<bool>(!mouseState.rgbButtons[button]);
}

myMath::Vector2 Input::GetmousePos(){
	return mousePos;
}

#pragma endregion

#pragma region	ゲームパッド

bool Input::StickInDeadZone(myMath::Vector2& thumb, const myMath::Vector2& deadRate){
	bool x = false;
	bool y = false;

	if ((thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.x&& thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.x)){
		thumb.x = 0.0f;
		x = true;
	}
	if ((thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.y&& thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * deadRate.y)){
		thumb.y = 0.0f;
		y = true;
	}

	if (x && y){
		return true;
	}

	return false;
}

void Input::JoyPadUpdate(){
	oldPadState = padState;
	ZeroMemory(&padState, sizeof(XINPUT_STATE));

	//コントローラー取得
	DWORD dwResult = XInputGetState(0, &padState);

	if (dwResult == ERROR_SUCCESS){
		//コントローラーが接続されている
		if (0 < shakeTimer){
			shakeTimer--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer == 0){
				vibration.wLeftMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
			}
			else{
				vibration.wLeftMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
			}

			XInputSetState(dwResult, &vibration);
		}
	}
	else{
		//コントローラーが接続されていない
	}
}

bool Input::JoyPadButtonTriggerPush(ControllerButton button){//押した瞬間
	//トリガー
	if (button == LT){
		return oldPadState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && JoyPadButtonKeepPush(button);
	}
	else if (button == RT){
		return oldPadState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && JoyPadButtonKeepPush(button);
	}
	else{
		return !(oldPadState.Gamepad.wButtons & button) && JoyPadButtonKeepPush(button);
	}
}

bool Input::JoyPadButtonKeepPush(ControllerButton button){//押されている間
	if (button == LT){
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < padState.Gamepad.bLeftTrigger;
	}
	else if (button == RT){
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < padState.Gamepad.bRightTrigger;
	}
	else{
		return padState.Gamepad.wButtons & button;
	}
}

bool Input::JoyPadButtonTriggerRelease(ControllerButton button){//離された瞬間
	//トリガー
	if (button == LT) {
		return oldPadState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && JoyPadButtonKeepPush(button);
	}
	else if (button == RT) {
		return oldPadState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && JoyPadButtonKeepPush(button);
	}
	else {
		return oldPadState.Gamepad.wButtons & button && !JoyPadButtonKeepPush(button);
	}
}

bool Input::JoyPadButtonKeepRelease(ControllerButton button){//離している間
	if (button == LT) {
		return !XINPUT_GAMEPAD_TRIGGER_THRESHOLD < padState.Gamepad.bLeftTrigger;
	}
	else if (button == RT) {
		return !XINPUT_GAMEPAD_TRIGGER_THRESHOLD < padState.Gamepad.bRightTrigger;
	}
	else {
		return !(padState.Gamepad.wButtons & button);
	}
}

bool Input::JoyPadStickTriggerPush(ControllerStick stickInput, const float& deadRange, const myMath::Vector2& deadRate){//押した瞬間
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;
	if (isLeftStick){
		oldVec = myMath::Vector2(oldPadState.Gamepad.sThumbLX, oldPadState.Gamepad.sThumbLY);
		vec = myMath::Vector2(padState.Gamepad.sThumbLX, padState.Gamepad.sThumbLY);
	}
	else{
		oldVec = myMath::Vector2(oldPadState.Gamepad.sThumbRX, oldPadState.Gamepad.sThumbRY);
		vec = myMath::Vector2(padState.Gamepad.sThumbRX, padState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate)){
		return false;
	}

	if (StickInDeadZone(vec, deadRate)){
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP){
		result = !(deadRange < (oldVec.y / STICK_INPUT_MAX)) && deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN){
		result = !(oldVec.y / STICK_INPUT_MAX < -deadRange) && vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT){
		result = !(deadRange < (oldVec.x / STICK_INPUT_MAX)) && deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT){
		result = !(oldVec.x / STICK_INPUT_MAX < -deadRange) && vec.x / STICK_INPUT_MAX < -deadRange;
	}
	else{
		assert(0);
	}

	return result;
}

bool Input::JoyPadStickKeepPush(ControllerStick stickInput, const float& deadRange, const myMath::Vector2& deadRate){//押されている間
	myMath::Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick){
		vec = myMath::Vector2(padState.Gamepad.sThumbLX, padState.Gamepad.sThumbLY);
	}
	else{
		vec = myMath::Vector2(padState.Gamepad.sThumbRX, padState.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, deadRate))return false;

	if (stickInput % 4 == L_UP){
		return deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN){
		return  vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT){
		return deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT){
		return  vec.x / STICK_INPUT_MAX < -deadRange;
	}

	assert(0);
	return false;
}

bool Input::JoyPadStickTriggerRelease(ControllerStick stickInput, const float& deadRange, const myMath::Vector2& deadRate){//離された瞬間
	myMath::Vector2 oldVec;
	myMath::Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick){
		oldVec = myMath::Vector2(oldPadState.Gamepad.sThumbLX, oldPadState.Gamepad.sThumbLY);
		vec = myMath::Vector2(padState.Gamepad.sThumbLX, padState.Gamepad.sThumbLY);
	}
	else{
		oldVec = myMath::Vector2(oldPadState.Gamepad.sThumbRX, oldPadState.Gamepad.sThumbRY);
		vec = myMath::Vector2(padState.Gamepad.sThumbRX, padState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate)){
		return false;
	}

	if (StickInDeadZone(vec, deadRate)){
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP){
		result = deadRange < (oldVec.y / STICK_INPUT_MAX) && !(deadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_DOWN){
		result = oldVec.y / STICK_INPUT_MAX < -deadRange && !(vec.y / STICK_INPUT_MAX < -deadRange);
	}
	else if (stickInput % 4 == L_RIGHT){
		result = deadRange < (oldVec.x / STICK_INPUT_MAX) && !(deadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_LEFT){
		result = oldVec.x / STICK_INPUT_MAX < -deadRange && !(vec.x / STICK_INPUT_MAX < -deadRange);
	}
	else{
		assert(0);
	}

	return result;
}

bool Input::JoyPadStickKeepRelease(ControllerStick stickInput, const float& deadRange, const myMath::Vector2& deadRate){//離している間
	return !JoyPadStickKeepPush(stickInput, deadRange, deadRate);
}

myMath::Vector2 Input::GetLeftStickVec(const myMath::Vector2& deadRate){
	myMath::Vector2 result(static_cast<float>(padState.Gamepad.sThumbLX), static_cast<float>(-padState.Gamepad.sThumbLY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

myMath::Vector2 Input::GetRightStickVec(const myMath::Vector2& deadRate){
	myMath::Vector2 result(static_cast<float>(padState.Gamepad.sThumbRX), static_cast<float>(-padState.Gamepad.sThumbRY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;;
}

void Input::ShakeController(const float& power, const int& span){
	if (!(0 < power && power <= 1.0f)){
		assert(0);
	}

	shakePower = power;
	shakeTimer = span;
}

#pragma endregion

Input* Input::GetInstance(){
	static Input instance;
	return &instance;
}