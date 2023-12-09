#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"GameObject.h"

class Reticle :public GameObject
{
private:

	InputManager* input_ = nullptr;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;
	uint32_t reticleTex2_ = 0;

	const float reticleSpeed_ = 2.0f;
	const float reticleLimit_ = 60.0f;

	Transform cameraTrans_;

	std::string name_ = "reticle";
	Transform colliderTrans_;
	CollisionData collisionData;

	static myMath::Vector2 addTargetAngle_;

	bool changeReticleFlag_ = false;
	uint8_t animationTimer_ = 0;
	uint8_t maxAnimationTime_ = 30;
	bool lockOnFlag_ = false;
	bool lockOnAttackFlag_ = false;

	int8_t cameraFlag_ = 0;

public:

	Reticle() = default;
	~Reticle() = default;

	//初期化処理
	void Initialize()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//オブジェクトの名前取得処理
	std::string GetName()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override;

	//死亡フラグの取得
	const bool GetIsDead()override;

	//死亡アニメーションフラグの取得
	const bool GetDeathAnimationFlag()override;

	//ロックオンフラグの取得
	const bool GetLockOnFlag()override;

	void LockOn()override;

	void CancelLockOn()override;

	const Transform& GetTransform()override;

	void Reset();

	const float GetReticleLimit();

	static const myMath::Vector2 GetAddTargetAngle();

	void ChangeReticle();

	void GetLockOnFlag(const bool flag);
	void GetLockOnAttackFlag(const bool flag);
	void GetCameraFlag(const int8_t flag);

private:

	void Move();

	void ReticleLimit();

	void ChangeReticleUpdate();
};