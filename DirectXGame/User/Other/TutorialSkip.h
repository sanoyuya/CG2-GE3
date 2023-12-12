#pragma once
#include"DrawOversight.h"
#include"GameTimer.h"
#include"InputManager.h"

/// <summary>
/// チュートリアルスキップ
/// </summary>
class TutorialSkip
{
private:

	InputManager* input_ = nullptr;
	GameTimer* gameTimer_ = nullptr;

	std::unique_ptr<Sprite2D>text_;//テキスト
	static uint32_t sTextTex_;

	bool drawFlag_ = false;

	uint16_t startTime_ = 0;

	bool animationFlag_ = false;
	uint8_t animationTimer_ = 0;
	const uint8_t isSkipAnimationTime_ = 100;
	const uint8_t maxAnimationTime_ = 180;
	float alpha_ = 0.0f;

	std::unique_ptr<Sprite2D>back_;
	static uint32_t sBackTex_;

public:

	void Initialize(GameTimer* gameTimer);

	void Update();

	void Draw();

	void SetGameStartTime(uint16_t startTime);

	void Reset();

	static void LoadAsset();
};