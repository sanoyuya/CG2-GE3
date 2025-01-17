#pragma once
#include"DrawOversight.h"

class LockOnAnimation
{
private:

	std::unique_ptr<Sprite>lockOnSprite_;
	Transform lockOnTrans_;
	static uint32_t sLockOnTex_;
	const float scale_ = 5.0f;
	const float scaleUpPower_ = 6.0f;
	const float scaleDownPower_ = 3.0f;

	bool lockOnAnimationFlag_ = false;
	float lockOnAnimationTimer_ = 0.0f;
	const float maxLockOnAnimationTimer_ = 15.0f;

public:

	void Initialize();

	void Create();

	void Cancel();

	void Update(const myMath::Vector3& position, Camera* camera);

	void Draw(Camera* camera);

	static void LoadAsset();
};