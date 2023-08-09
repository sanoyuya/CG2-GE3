#pragma once
#include"DrawOversight.h"
#include"PlayerEngineSmokeParticleEmitter.h"
#include"GameObject.h"

enum class BulletOwner
{
	Player,
	Enemy
};

class Bullet:public GameObject
{
private:

	Camera* camera_ = nullptr;

	std::string name_ = "bullet";

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	myMath::Vector3 directionVector_;//�����x�N�g��
	const float speed_ = 1.5f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

	BulletOwner owner_ = BulletOwner::Player;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

public:

	Bullet();
	~Bullet();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	void SetCamera(Camera* camera);
	void SetPos(const myMath::Vector3& position);
	void SetDirectionVector(const myMath::Vector3& directionVector);
	void SetOwner(BulletOwner owner);

public:

	void SmokeUpdate();

	bool GetIsDead();

	void OnCollision();

	const myMath::Vector3& GetPosition();
};