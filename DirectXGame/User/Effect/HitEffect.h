#pragma once
#include"DrawOversight.h"
#include"Camera.h"

class HitEffect
{
private:

	std::unique_ptr<Sprite>hit_;
	Transform hitTrans_;
	static uint32_t hitTex_;

	bool animationFlag_ = false;
	float animationTimer_ = 0.0f;
	const float maxAnimationTime_ = 60.0f;
	float posY = 0.0f;

	myMath::Vector3 pos_ = {};
	float alpha_ = 1.0f;
	const float scale_ = 25.0f;
	const float upPosAmount_ = 4.0f;

public:

	static void LoadAsset();

	void Initialize();

	void Create(const myMath::Vector3& pos);

	void Update(Camera* camera);

	void Draw(Camera* camera);
};

