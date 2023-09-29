#pragma once
#include"Enemy.h"
#include"HitEffect.h"

class NormalEnemy:public Enemy
{
private:

	std::string name_ = "enemy";

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	float spawnTime_ = 0.0f;
	float deathTime_ = 0.0f;

	bool spawnFlag_ = false;
	bool isDead_ = false;

	float bulletTimer = 0.0f;
	const float maxBulletTime = 60.0f;

	bool spawnAnimationFlag_ = false;
	uint8_t spawnAnimationTimer_ = 0;
	const uint8_t maxSpawnAnimationTime_ = 60;

	bool deathAnimationFlag_ = false;
	uint8_t deathAnimationTimer_ = 0;
	const uint8_t maxDeathAnimationTime_ = 60;

	std::unique_ptr<EnemyDeathParticleEmitter>emitter_;
	std::unique_ptr<EnemySpawnParticleEmitter>spawnEmitter_;

	bool lockOnFlag = false;

	CollisionData collisionData_;

	std::unique_ptr<LockOnAnimation>lockOnAnimation_;

	std::unique_ptr<HitEffect>hitEffect_;

public:

	NormalEnemy()=default;
	~NormalEnemy();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	const Transform& GetTransform();

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData();

	//オブジェクトの衝突判定処理
	void OnCollision();

	const bool GetIsDead();

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag();

	void LockOn();

	void CancelLockOn();

	const bool GetLockOnFlag();

public://セッター

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	void SetPosition(const myMath::Vector3& position);
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	void SetRotation(const myMath::Vector3& rotation);
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	void SetColliderSize(const float size);
	//blenderで出力したデータを読み込むときにスポーンタイマーをセットする関数
	void SetSpawnTimer(const float timer);
	//blenderで出力したデータを読み込むときに死亡タイマーをセットする関数
	void SetDeathTimer(const float timer);

	void SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty);

public://ゲッター

	bool GetSpawnFlag();

	const Transform& GetTrans();

private:

	void BulletUpdate();

	void SpawnUpdate();

	void DeathUpdate();
};