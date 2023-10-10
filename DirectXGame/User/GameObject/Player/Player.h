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
#include"BulletManager.h"

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
	BulletManager* bulletManager_ = nullptr;

	std::string name_ = "player";

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	uint32_t playerTex_ = 0;

	Transform cameraTrans_;

	myMath::Vector3 directionVector_;//方向ベクトル(ローカル)
	myMath::Vector3 parentToDirectionVector_;//親子を反映させた方向ベクトル

	std::unique_ptr<Reticle>reticle_;

	const float moveSpeed_ = 0.125f;

	int8_t maxHp_ = 10;
	int8_t hp_ = maxHp_;
	std::unique_ptr<HPBar>hpBar_;

	bool deathFlag_ = false;

	bool damageFlag_ = false;

	myMath::Vector3 targetPos_ = {};

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	std::unique_ptr<PlayerDeathAnimation>deathAnimation_;

	CollisionData collisionData_;

	bool lockOnAttackFlag_ = false;
	int8_t lockOnTimer_ = 0;

	uint8_t coolTime_ = 0;
	const uint8_t maxCoolTime_ = 60;
	bool isBulletAttack_ = false;

	Transform controlTrans_;

public:

	Player() = default;
	~Player();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData();

	void OnCollision();

	//死亡フラグの取得
	const bool GetIsDead();

	const bool GetDeathAnimationFlag();

	void LockOn();

	void CancelLockOn();

	//ロックオンフラグの取得
	const bool GetLockOnFlag();

	void Reset();

	const bool GetDamageFlag();

	const Transform& GetTransform();

	const uint8_t GetHp();

	void SetDamageFlag(const bool damageFlag);

	const myMath::Vector3& GetAddTargetPos();

	void SetCamera(Camera* camera);

	void SetBulletManager(BulletManager* bulletManager);

	const bool GetIsBulletAttack();

private:

	void Move();

	void Rotation(Camera* camera);

	void NormalBulletAttack();

	void SmokeUpdate(Camera* camera);

	void LockOnAttack();

	void ImGuiUpdate();
};