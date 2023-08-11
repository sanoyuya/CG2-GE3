#pragma once
#include"Bullet.h"

class NormalBullet:public Bullet
{
private:

	std::string name_ = "normalBullet";

	myMath::Vector3 directionVector_;//•ûŒüƒxƒNƒgƒ‹

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	const float speed_ = 1.5f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

	BulletOwner owner_ = BulletOwner::Player;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

public:

	void Initialize();
	void Update();
	void Draw();
	std::string GetName();

	void SetPos(const myMath::Vector3& position);
	void SetOwner(BulletOwner owner);

	void SetDirectionVector(const myMath::Vector3& directionVector);

	BulletOwner GetOwner();

	bool GetIsDead();

	void OnCollision();

	const myMath::Vector3& GetPosition();

private:

	void SmokeUpdate();
};