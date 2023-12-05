#pragma once
#include"BulletBase.h"
#include"DrawOversight.h"
#include"PlayerEngineSmokeParticleEmitter.h"
#include"EnemyDeathParticleEmitter.h"

class NormalBullet :public BulletBase
{
private:

	Camera* camera_ = nullptr;

	std::string name_ = "bullet";

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	myMath::Vector3 directionVector_;//方向ベクトル
	const float speed_ = 6.0f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

	BulletOwner owner_ = BulletOwner::Player;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	CollisionData collisionData_;

	bool deathAnimationFlag_ = false;
	uint8_t animationTimer_ = 0;
	uint8_t maxAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>deathParticleEmitter_;
	bool deathFlag_ = false;

public://BulletBaseで必要な奴

	//デストラクタ
	~NormalBullet();

	//初期化処理
	void Initialize()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//オブジェクトの名前取得処理
	std::string GetName()override;

	const Transform& GetTransform()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override;

	void BulletDeathAnimation()override;

	const bool GetDeathFlag()override;

	//死亡フラグの取得
	const bool GetIsDead()override;

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag()override;

	//ロックオン
	void LockOn()override;

	void CancelLockOn()override;

	const bool GetLockOnFlag()override;

	void SetCamera(Camera* camera)override;
	void SetPos(const myMath::Vector3& position)override;
	void SetDirectionVector(const myMath::Vector3& directionVector)override;
	void SetOwner(BulletOwner owner)override;
	void SetName(const std::string& name)override;
	void SetTargetPos(GameObject* lockOnEnemy)override;
	void SetControlPos(const myMath::Vector3& position)override;
};