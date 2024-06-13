#include "GameTimer.h"
#include<imgui.h>

void GameTimer::Update()
{
	flameCount_ += timeSpeed_;

	intTime_ = static_cast<uint32_t>(flameCount_ / 60);
}

void GameTimer::Reset()
{
	flameCount_ = 0;
	intTime_ = 0;
}

void GameTimer::ImGuiUpdate()
{
	ImGui::Begin("GameTimer");
	ImGui::SliderFloat("nowFlame", &flameCount_, 0, 1800);
	ImGui::SliderFloat("timeSpeed", &timeSpeed_, 0.1f, 5.0f);
	ImGui::Text("nowTime:%d", intTime_);
	ImGui::End();
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

float GameTimer::GetTimeSpeed()
{
	return timeSpeed_;
}

void GameTimer::SetTimeSpeed(const float timeSpeed)
{
	timeSpeed_ = timeSpeed;
}

void GameTimer::SetGameTime(const uint32_t time)
{
	gameTime_ = time;
}

void GameTimer::SetFlameTime(const float time)
{
	flameCount_ = time;
}