#pragma once
#include"DrawOversight.h"

class GameTimer
{
private:

	float flameCount_ = 0.0f;

	uint32_t intTime_ = 0;

	float timeSpeed_ = 1.0f;

	//ゲーム全体のフレーム数
	const uint32_t gameTime_ = 60 * 60 * 1;//1秒間のフレーム数*1分間の秒数*全体の時間(分)

public:

	GameTimer() = default;
	~GameTimer() = default;

	void Update();

	void Reset();

	const float& GetFlameCount();

	const uint32_t& GetIntTime();

	const uint32_t& GetGameTime();

	void SetTimeSpeed(const float timeSpeed);
};