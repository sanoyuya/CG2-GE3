#include "GameTimer.h"

void GameTimer::Update()
{
	flameCount_ += timeSpeed_;

	intTime_ = static_cast<uint32_t>(flameCount_ / 60);
}

void GameTimer::Reset()
{
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

const uint32_t& GameTimer::GetGameTime()
{
	return gameTime_;
}

void GameTimer::SetTimeSpeed(const float timeSpeed)
{
	timeSpeed_ = timeSpeed;
}