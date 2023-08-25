#pragma once
#include"DrawOversight.h"
#include"Camera.h"
#include"InputManager.h"
#include"GameObject.h"

class Reticle:public GameObject
{
private:

	InputManager* input_ = nullptr;
	Camera* camera_ = nullptr;

	std::unique_ptr<Sprite>reticle_;
	Transform reticleTrans_;
	uint32_t reticleTex_ = 0;

	const float reticleSpeed_ = 1.5f;
	const float reticleLimit_ = 45.0f;

	Transform cameraTrans_;

	std::string name_ = "reticle";
	CollisionData collisionData;

public:

	Reticle() = default;
	~Reticle() = default;

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

	//ロックオンフラグの取得
	const bool GetLockOnFlag();

	void LockOn();

	void CancelLockOn();

	void Reset();

	const float GetReticleLimit();

	const Transform& GetTransform();

	void SetCamera(Camera* camera);

private:

	void Move();

	void ReticleLimit();
};