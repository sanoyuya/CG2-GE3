#pragma once
#include"DrawOversight.h"
#include"GameTimer.h"

enum class TextName
{
	MOVE,
	ATTACK,
	CAMERAMOVE,
	CHARGEATTACK,
	READY,
	GO
};

/// <summary>
/// テキスト
/// </summary>
class Text
{
private:

	std::array<std::unique_ptr<Sprite2D>, 4>frame_;//縁
	static uint32_t sFrameTex_;

	std::unique_ptr<Sprite2D>text_;//テキスト本体
	uint32_t textTex_ = 0;
	float textAlpha_ = 0.0f;

	myMath::Vector2 center_ = {};
	myMath::Vector2 frameSize_ = {};

	std::array<myMath::Vector2, 4>framePos_;
	std::array<float, 4>frameScale_;

	const float time_ = 60.0f;

	bool drawFrag_ = false;
	static std::array<uint32_t,6> sTextTex_;

public:

	void Initialize(const TextName& textFlag);

	void Update(GameTimer* gameTimer, uint8_t startTime, uint8_t endTime);

	void Draw();

	static void LoadAsset();

private:

	void Begin(GameTimer* gameTimer, uint8_t startTime);

	void End(GameTimer* gameTimer, uint8_t endTime);
};