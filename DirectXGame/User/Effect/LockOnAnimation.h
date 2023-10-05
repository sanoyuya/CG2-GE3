#pragma once
#include"DrawOversight.h"

class LockOnAnimation
{
private:

	std::unique_ptr<Sprite>lockOnSprite_;
	Transform lockOnTrans_;
	uint32_t lockOnTex_ = 0;

	bool lockOnAnimationFlag_ = false;
	float lockOnAnimationTimer_ = 0.0f;

public:

	void Initialize();

	void Create();

	void Cancel();

	void Update(const myMath::Vector3& position, Camera* camera);

	void Draw(Camera* camera);
};