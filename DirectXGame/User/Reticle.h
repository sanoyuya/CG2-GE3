#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"

class Reticle
{
private:

	InputManager* input_ = nullptr;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

	const float reticleSpeed_ = 0.5f;
	const float reticleLimit_ = 15.0f;

	Transform cameraTrans_;

public:

	void Initialize();

	void Update(Camera* camera);

	void Draw(Camera* camera);

	void Reset();

	const float GetReticleLimit();

	const Transform& GetTransform();

private:

	void Move();

	void ReticleLimit();
};