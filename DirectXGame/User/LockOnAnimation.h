#pragma once
#include"DrawOversight.h"

class LockOnAnimation
{
private:

	std::unique_ptr<Sprite>lockOnSprite_;
	Transform lockOnTrans_;
	uint32_t lockOnTex_ = 0;

public:

	void Initialize();

	void Create();

	void Update();

	void Draw();
};