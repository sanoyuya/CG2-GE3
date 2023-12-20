#pragma once
#include"Enemy.h"
#include"HitEffect.h"

class NormalEnemy:public Enemy
{
private:

	std::string name_ = "enemy";
	Transform iniPos_;
	uint16_t actionTimer = 0;

	std::unique_ptr<Model>enemy_;
	Transform enemyTrans_;
	float spawnTime_ = 0.0f;
	float deathTime_ = 0.0f;

	bool spawnFlag_ = false;
	bool isDead_ = false;
	bool isAttack = false;

	float bulletTimer = 0.0f;
	float maxBulletTime = 0.0f;

	bool spawnAnimationFlag_ = false;
	uint8_t spawnAnimationTimer_ = 0;
	const uint8_t maxSpawnAnimationTime_ = 60;

	bool deathAnimationFlag_ = false;
	uint8_t deathAnimationTimer_ = 0;
	const uint8_t maxDeathAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>emitter_;
	std::unique_ptr<EnemySpawnParticleEmitter>spawnEmitter_;

	bool lockOnFlag_ = false;

	CollisionData collisionData_;

	std::unique_ptr<LockOnAnimation>lockOnAnimation_;

	std::unique_ptr<HitEffect>hitEffect_;

public:

	NormalEnemy()=default;
	~NormalEnemy();

	void Initialize()override;

	void Update()override;

	void Draw()override;

	std::string GetName()override;

	const Transform& GetTransform()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override;

	const bool GetIsDead()override;

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag()override;

	void LockOn()override;

	void CancelLockOn()override;

	const bool GetLockOnFlag()override;

public://セッター

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	void SetPosition(const myMath::Vector3& position)override;
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	void SetRotation(const myMath::Vector3& rotation)override;
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	void SetColliderSize(const float size)override;
	//blenderで出力したデータを読み込むときにスポーンタイマーをセットする関数
	void SetSpawnTimer(const float timer)override;
	//blenderで出力したデータを読み込むときに死亡タイマーをセットする関数
	void SetDeathTimer(const float timer)override;

	void SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty)override;

	void SetIsAttack(const bool flag)override;

public://ゲッター

	const bool GetSpawnFlag()override;

	const Transform& GetTrans()override;

private:

	void BulletUpdate();

	void SpawnUpdate();

	void DeathUpdate();
};