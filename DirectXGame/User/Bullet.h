#pragma once
#include"DrawOversight.h"

class Bullet
{
private:

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	myMath::Vector3 directionVector_;//•ûŒüƒxƒNƒgƒ‹
	const float speed_ = 5.0f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

public:

	Bullet();
	~Bullet();

	void Initialize(const myMath::Vector3& position,const myMath::Vector3& directionVector);

	void Update(Camera* camera);

	void Draw();

public:

	bool GetIsDead();
};