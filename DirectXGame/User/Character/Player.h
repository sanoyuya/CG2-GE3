#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"myMath.h"
#include"PlayerEngineSmokeParticleEmitter.h"
#include"EnemyDeathParticleEmitter.h"
#include"HPBar.h"
#include"Reticle.h"
#include"PlayerDeathAnimation.h"
#include"GameObject.h"

struct PlayerData
{
	myMath::Vector3 pos;
	myMath::Vector3 rotation;
	myMath::Vector3 scale;
};

class Player:public GameObject
{
private:

	InputManager* input_ = nullptr;
	Camera* camera_ = nullptr;

	std::string name_ = "player";

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_ = 0;

	Transform cameraTrans_;

	myMath::Vector3 directionVector_;//方向ベクトル(ローカル)
	myMath::Vector3 parentToDirectionVector_;//親子を反映させた方向ベクトル

	std::unique_ptr<Reticle>reticle_;

	const float moveSpeed_ = 0.125f;

	int8_t maxHp_ = 100;
	int8_t hp_ = maxHp_;
	std::unique_ptr<HPBar>hpBar_;

	bool deathFlag_ = false;

	bool damageFlag_ = false;

	myMath::Vector3 targetPos = {};

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	std::unique_ptr<PlayerDeathAnimation>deathAnimation_;

public:

	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	void Reset();

	void HpSub();

	const bool GetDamageFlag();

	const Transform& GetTransform();

	const uint8_t GetHp();

	void SetDamageFlag(const bool damageFlag);

	const myMath::Vector3& GetAddTargetPos();

	const bool& GetDeathFlag();

	void SetCamera(Camera* camera);

private:

	void Move();

	void Rotation(Camera* camera);

	void BulletUpdate(Camera* camera);

	void BulletDraw();

	void SmokeUpdate(Camera* camera);
};