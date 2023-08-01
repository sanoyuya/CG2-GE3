#pragma once
#include"DrawOversight.h"

class HPBar
{
private:

	std::unique_ptr<Sprite>hpBar_;
	uint32_t hpBarTex_ = 0;
	myMath::Vector4 hpColor = {};

	int8_t maxHp_ = 0;
	int8_t hp_ = 0;

	myMath::Vector2 leftUpPoint_ = {};

public:

	HPBar() = default;
	~HPBar() = default;

	void Initialize(const int8_t maxHp, const myMath::Vector2 leftUpPoint);

	void Update(const int8_t hp);

	void Draw();
};