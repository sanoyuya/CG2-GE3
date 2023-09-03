#pragma once
#include"BulletBase.h"
#include"DrawOversight.h"
#include"PlayerEngineSmokeParticleEmitter.h"

class NormalBullet :public BulletBase
{
private:

	Camera* camera_ = nullptr;

	std::string name_ = "bullet";

	bool isDead_ = false;
	uint8_t deathTimer_ = 0;
	const uint8_t maxDeathTime_ = 60;

	myMath::Vector3 directionVector_;//方向ベクトル
	const float speed_ = 1.5f;

	std::unique_ptr<Model>bullet_;
	uint32_t bulletTex_ = 0;
	Transform bulletTrans_;

	BulletOwner owner_ = BulletOwner::Player;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	CollisionData collisionData_;

public://BulletBaseで必要な奴

	//デストラクタ
	~NormalBullet();

	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//オブジェクトの名前取得処理
	std::string GetName();

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData();

	//オブジェクトの衝突判定処理
	void OnCollision();

	//死亡フラグの取得
	const bool GetIsDead();

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag();

	//ロックオン
	void LockOn();

	void CancelLockOn();

	const bool GetLockOnFlag();

	void SetCamera(Camera* camera);
	void SetPos(const myMath::Vector3& position);
	void SetDirectionVector(const myMath::Vector3& directionVector);
	void SetOwner(BulletOwner owner);
	void SetName(const std::string& name);
	void SetTargetPos(const myMath::Vector3& position);
	void SetControlPos(const myMath::Vector3& position);

private:

	void SmokeUpdate();
};