#pragma once
#include"DrawOversight.h"

class HPBar
{
private:

	std::unique_ptr<Sprite>hpBar_;
	static uint32_t sHpBarTex_;
	myMath::Vector4 hpColor = {};
	myMath::Vector2 hpScale_ = { 25.0f,14.0f };

	myMath::Vector4 greenColor_ = { 130.0f / 255.0f,174.0f / 255.0f,70.0f / 255.0f,1.0f };
	myMath::Vector4 yellowColor_ = { 255.0f / 255.0f,217.0f / 255.0f,0.0f / 255.0f,1.0f };
	myMath::Vector4 redColor_ = { 255.0f / 255.0f,0.0f / 255.0f,0.0f / 255.0f,1.0f };

	std::unique_ptr<Sprite>hpBarFlame_;
	static uint32_t sHpBarFlameTex_;

	int8_t maxHp_ = 0;
	int8_t hp_ = 0;

	myMath::Vector2 leftUpPoint_ = {};

	bool animationFlag_ = false;
	uint8_t animationTimer_ = 0;
	uint8_t maxAnimationTimer_ = 60;

	float hpBarScale_ = 0.0f;

public:

	HPBar() = default;
	~HPBar() = default;

	void Initialize(const int8_t maxHp, const myMath::Vector2 leftUpPoint);

	void Update(const int8_t hp);

	void Draw();

	static void LoadAsset();
};