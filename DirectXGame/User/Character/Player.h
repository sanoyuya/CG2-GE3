#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"myMath.h"
#include"Character.h"
#include"PlayerEngineSmokeParticleEmitter.h"

struct PlayerData
{
	myMath::Vector3 pos;
	myMath::Vector3 rotation;
	myMath::Vector3 scale;
};

class Player:public Character
{
private:

	InputManager* input_ = nullptr;

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_ = 0;

	Transform cameraTrans_;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

	myMath::Vector3 directionVector_;//方向ベクトル(ローカル)
	myMath::Vector3 parentToDirectionVector_;//親子を反映させた方向ベクトル

	const float moveSpeed_ = 0.125f;
	const float reticleSpeed_ = 0.5f;
	const float reticleLimit_ = 15.0f;

	int8_t hp_ = 100;
	int8_t maxHp_ = 100;
	std::unique_ptr<Sprite>hpBar_;
	uint32_t hpBarTex_ = 0;

	bool damageFlag_ = false;

	myMath::Vector3 targetPos = {};

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

public:

	Player();
	~Player();

	void Initialize();

	void Update(Camera* camera);

	void Draw(Camera* camera);

	void Reset();

	void HpSub();

	const bool& GetDamageFlag();

	const Transform& GetTransform();

	const uint8_t GetHp();

	void SetDamageFlag(const bool& damageFlag);

	const myMath::Vector3& GetAddTargetPos();

private:

	void Move();

	void Rotation(Camera* camera);

	void ReticleMove();

	void MoveLimit();

	void ReticleLimit();

	void BulletUpdate(Camera* camera);

	void BulletDraw();

	void SmokeUpdate(Camera* camera);
};