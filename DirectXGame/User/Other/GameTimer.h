#pragma once
#include"DrawOversight.h"

class GameTimer
{
private:

	float flameCount_ = 0.0f;

	float floatTime_ = 0.0f;
	uint32_t intTime_ = 0;

	float timeSpeed_ = 1.0f;

public:

	GameTimer() = default;
	~GameTimer() = default;

	void Update();

	void Reset();

	const float& GetFlameCount();

	const uint32_t& GetIntTime();

	void SetTimeSpeed(const float timeSpeed);
};