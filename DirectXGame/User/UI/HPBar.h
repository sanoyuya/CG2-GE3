#pragma once
#include"DrawOversight.h"

class HPBar
{
private:

	std::unique_ptr<Sprite>hpBar_;
	static uint32_t sHpBarTex_;
	myMath::Vector4 hpColor = {};

	std::unique_ptr<Sprite>hpBarFlame_;
	static uint32_t sHpBarFlameTex_;

	int8_t maxHp_ = 0;
	int8_t hp_ = 0;

	myMath::Vector2 leftUpPoint_ = {};

	bool animationFlag_ = false;
	uint8_t animationTimer_ = 0;
	uint8_t maxAnimationTimer_ = 30;

	float hpBarScale_ = 0.0f;

public:

	HPBar() = default;
	~HPBar() = default;

	void Initialize(const int8_t maxHp, const myMath::Vector2 leftUpPoint);

	void Update(const int8_t hp);

	void Draw();

	static void LoadAsset();
};