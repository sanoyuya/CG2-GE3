#pragma once
#include"BulletBase.h"
#include"DrawOversight.h"

class TripleBullet :public BulletBase
{
private:

	std::string name_ = "bullet";

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

public:

	//デストラクタ
	~TripleBullet();

	//初期化処理
	void Initialize()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//オブジェクトの名前取得処理
	std::string GetName()override;

	const Transform& GetTransform()override = 0;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override = 0;

	void BulletDeathAnimation()override = 0;

	const bool GetDeathFlag()override = 0;

	//死亡フラグの取得
	const bool GetIsDead()override;

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag()override = 0;

	//ロックオン
	void LockOn()override = 0;

	void CancelLockOn()override = 0;

	const bool GetLockOnFlag()override = 0;

	void SetPos(const myMath::Vector3& position)override;
	void SetDirectionVector(const myMath::Vector3& directionVector)override;
	void SetOwner(BulletOwner owner)override;
	void SetName(const std::string& name)override;
	void SetTargetPos(GameObject* lockOnEnemy)override = 0;
	void SetControlPos(const myMath::Vector3& position)override = 0;
};