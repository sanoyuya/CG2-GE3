#include "GameTimer.h"

void GameTimer::Update()
{
	flameCount_ += timeSpeed_;
	floatTime_ += timeSpeed_;

	if (floatTime_ >= 60.0f)
	{
		intTime_++;
		floatTime_ = 0.0f;
	}
}

void GameTimer::Reset()
{
	floatTime_ = 0.0f;
	intTime_ = 0;
}

const float& GameTimer::GetFlameCount()
{
	return flameCount_;
}

const uint32_t& GameTimer::GetIntTime()
{
	return intTime_;
}

void GameTimer::SetTimeSpeed(const float timeSpeed)
{
	timeSpeed_ = timeSpeed;
}