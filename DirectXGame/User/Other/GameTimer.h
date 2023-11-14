#pragma once
#include"DrawOversight.h"

class GameTimer
{
private:

	float flameCount_ = 0.0f;

	uint32_t intTime_ = 0;

	float timeSpeed_ = 1.0f;

	//ゲーム全体のフレーム数
	uint32_t gameTime_ = 0;//1秒間のフレーム数*1分間の秒数*全体の時間(分)

public:

	GameTimer() = default;
	~GameTimer() = default;

	void Update();

	void Reset();

	void ImGuiUpdate();

	const float& GetFlameCount();

	const uint32_t& GetIntTime();

	const uint32_t& GetGameTime();

	void SetTimeSpeed(const float timeSpeed);

	void SetGameTime(const uint32_t time);
};