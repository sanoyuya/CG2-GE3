#pragma once
#include"myMath.h"
#include <string>
#include"Transform.h"
#include"Camera.h"
#include"GameTimer.h"

struct CollisionData
{
	myMath::Vector3 center = {};
	float radius = 0.0f;

	myMath::Vector3 scale;

	myMath::Vector3 rayStartPos = {};
	myMath::Vector3 rayEndPos = {};
};

//オブジェクト基底クラス
class GameObject
{
protected:

	static Camera* sCamera_;
	static GameTimer* sGameTimer_;

public:

	static void SetCamera(Camera* camera);
	static void SetGameTimer(GameTimer* gameTimer);

public:

	//デストラクタ
	virtual ~GameObject() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//オブジェクトの名前取得処理
	virtual std::string GetName() = 0;

	virtual const Transform& GetTransform() = 0;

	//オブジェクトの当たり判定取得処理
	virtual const CollisionData& GetCollisionData() = 0;

	//オブジェクトの衝突判定処理
	virtual void OnCollision() = 0;

	//弾の爆発処理
	virtual void BulletDeathAnimation() {};

	virtual const bool GetDeathFlag() { return false; };

	virtual const bool GetSpawnFlag() { return false; };
	//死亡フラグの取得
	virtual const bool GetIsDead() { return false; };

	//死亡アニメーションフラグの取得
	virtual const bool GetDeathAnimationFlag() { return false; };

	//ロックオン
	virtual void LockOn() = 0;

	//ロックオン解除
	virtual void CancelLockOn() = 0;

	//ロックオンフラグの取得
	virtual const bool GetLockOnFlag() { return false; };
};