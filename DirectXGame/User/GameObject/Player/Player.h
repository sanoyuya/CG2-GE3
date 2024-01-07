#pragma once
#include"DrawOversight.h"
#include"RailCamera.h"
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
	RailCamera* camera_ = nullptr;
	BulletManager* bulletManager_ = nullptr;

	std::string name_ = "player";

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	static uint32_t sPlayerTex_;

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

	static myMath::Vector3 targetPos_;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	std::unique_ptr<PlayerDeathAnimation>deathAnimation_;

	CollisionData collisionData_;

	bool lockOnAttackFlag_ = false;
	int8_t lockOnTimer_ = 0;

	uint8_t coolTime_ = 0;
	const uint8_t maxCoolTime_ = 30;
	bool isBulletAttack_ = false;

	Transform controlTrans_;

	static CameraFlag cameraFlag_;
	int8_t cameraFlagNum_ = 0;

	myMath::Vector3 addMovePos_ = {};

public:

	Player() = default;
	~Player();

	void Initialize()override;

	void Update()override;

	void Draw()override;

	std::string GetName()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	void OnCollision()override;

	//死亡フラグの取得
	const bool GetIsDead()override;

	const bool GetDeathAnimationFlag()override;

	void LockOn()override;

	void CancelLockOn()override;

	//ロックオンフラグの取得
	const bool GetLockOnFlag()override;

	const Transform& GetTransform()override;

	static void LoadAsset();

	void Reset();

	void SetCamera(RailCamera* camera);

	void SetBulletManager(BulletManager* bulletManager);

	const bool GetDamageFlag();

	const uint8_t GetHp();

	void SetDamageFlag(const bool damageFlag);

	static const myMath::Vector3& GetAddTargetPos();

	const bool GetIsBulletAttack();

	static const CameraFlag& GetCameraFlag();

	const myMath::Vector3& GetPredictionPoint();

	void ImGuiUpdate();

private:

	void Move();

	void Rotation();

	void CameraRotation();

	void NormalBulletAttack();

	void SmokeUpdate();

	void LockOnAttack();
};