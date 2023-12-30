#pragma once
#include"Enemy.h"
#include"HitEffect.h"

enum class ActionPhase
{
	//移動
	MOVE,
	//待機
	WAIT,
	//逃走
	ESCAPE
};

class MoveEnemy :public Enemy
{
private:

	std::string name_ = "enemy";

	std::unique_ptr<Model>enemy_;
	Transform enemyTrans_;
	float spawnTime_ = 0.0f;
	float deathTime_ = 0.0f;

	bool spawnFlag_ = false;
	bool isDead_ = false;
	AttackProperty attackProperty_;

	float bulletTimer_ = 0.0f;
	float maxBulletTime_ = 60.0f;

	bool spawnAnimationFlag_ = false;
	uint8_t spawnAnimationTimer_ = 0;

	bool deathAnimationFlag_ = false;
	uint8_t deathAnimationTimer_ = 0;

	std::unique_ptr<EnemyDeathParticleEmitter>emitter_;
	std::unique_ptr<EnemySpawnParticleEmitter>spawnEmitter_;

	bool lockOnFlag_ = false;
	std::unique_ptr<Sprite>lockOnSprite_;
	Transform lockOnTrans_;
	uint32_t lockOnTex_ = 0;

	CollisionData collisionData_;

	MoveEnemyProperty moveEnemyProperty_;

	ActionPhase phase = ActionPhase::MOVE;
	uint16_t actionTimer = 0;
	
	myMath::Vector3 waitFinishPos = {};
	myMath::Vector3 waitFinishRot = {};

	std::unique_ptr<LockOnAnimation>lockOnAnimation_;

	std::unique_ptr<HitEffect>hitEffect_;

public:

	MoveEnemy() = default;
	~MoveEnemy();

	void Initialize()override;

	void Update()override;

	void PhaseUpdate();

	void PhaseMove(const myMath::Vector3& startPosition, const myMath::Vector3& endPosition, const myMath::Vector3& startRotation, const myMath::Vector3& endRotation,const float maxTime);

	void Draw()override;

	std::string GetName()override;

	const Transform& GetTransform()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override;

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

	void SetAttackProperty(const AttackProperty property)override;

public://ゲッター

	const bool GetIsDead()override;

	const bool GetSpawnFlag()override;

	const Transform& GetTrans()override;

private:

	void BulletUpdate();

	void SpawnUpdate();

	void DeathUpdate();
};