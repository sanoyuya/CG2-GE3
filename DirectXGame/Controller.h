#pragma once
#include<Windows.h>
#include"myMath.h"
#include <Xinput.h>

class Controller{
private:
	//XINPUT(コントローラー用)
	XINPUT_STATE xinputState;
	XINPUT_STATE oldXinputState;
	float shakePower = 0.0f;;
	int shakeTimer = 0;

public:
	enum CONTROLLER {
		B = XINPUT_GAMEPAD_B,
		A = XINPUT_GAMEPAD_A,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
		LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		LT, RT
	};
	enum CONTROLLER_STICK {
		L_UP, L_DOWN, L_LEFT, L_RIGHT,
		R_UP, R_DOWN, R_LEFT, R_RIGHT, XBOX_STICK_NUM
	};
	void Initialize();
	void Update();

	//デッドゾーンに入っているか(DeadRate : デッドゾーン判定の度合い、1.0fだとデフォルト)
	bool StickInDeadZone(myMath::Vector2& Thumb,const myMath::Vector2& DeadRate);
	bool OnTrigger(CONTROLLER Button);
	bool OnTrigger(CONTROLLER StickInput, const float& DeadRange = 0.3f, const myMath::Vector2& DeadRate = { 1.0f,1.0f });
	bool Input(CONTROLLER Button);
	bool Input(CONTROLLER_STICK StickInput, const float& DeadRange = 0.3f, const myMath::Vector2& DeadRate = { 1.0f,1.0f });
	bool OffTrigger(CONTROLLER Button);
	bool OffTrigger(CONTROLLER_STICK StickInput, const float& DeadRange = 0.3f, const myMath::Vector2& DeadRate = { 1.0f,1.0f });

	//デッドゾーン判定の度合い(1.0fだとデフォルト採用)
	myMath::Vector2 GetLeftStickVec(const myMath::Vector2& DeadRate = { 1.0f,1.0f });
	myMath::Vector2 GetRightStickVec(const myMath::Vector2& DeadRate = { 1.0f,1.0f });
	void ShakeController(const float& Power, const int& Span);
};

