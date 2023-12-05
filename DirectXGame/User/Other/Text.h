#pragma once
#include"DrawOversight.h"
#include"GameTimer.h"

/// <summary>
/// テキスト
/// </summary>
class Text
{
private:

	std::array<std::unique_ptr<Sprite2D>, 4>frame_;//縁
	uint32_t frameTex_ = 0;

	std::unique_ptr<Sprite2D>text_;//テキスト本体
	uint32_t textTex_ = 0;
	float textAlpha_ = 0.0f;

	myMath::Vector2 center_ = {};
	myMath::Vector2 frameSize_ = {};

	std::array<myMath::Vector2, 4>framePos_;
	std::array<float, 4>frameScale_;

	const float time_ = 60.0f;

	bool drawFrag_ = false;

public:

	void Initialize(const std::string& filePath);

	void Update(GameTimer* gameTimer, uint8_t startTime, uint8_t endTime);

	void Draw();

private:

	void Begin(GameTimer* gameTimer, uint8_t startTime);

	void End(GameTimer* gameTimer, uint8_t endTime);
};