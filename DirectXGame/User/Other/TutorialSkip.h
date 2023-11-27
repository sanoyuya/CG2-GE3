#pragma once
#include"DrawOversight.h"
#include"GameTimer.h"
#include"InputManager.h"

class TutorialSkip
{
private:


	InputManager* input_ = nullptr;
	GameTimer* gameTimer_ = nullptr;

	std::unique_ptr<Sprite2D>text_;//テキスト
	uint32_t textTex_ = 0;

	bool drawFlag_ = false;

	uint16_t startTime_ = 0;

public:

	void Initialize(GameTimer* gameTimer);

	void Update();

	void Draw();

	void SetGameStartTime(uint16_t startTime);
};