#pragma once
#include"GameObject.h"
#include"Camera.h"

enum class BulletOwner
{
	Player,
	Enemy
};

class BulletBase :public GameObject
{
public://GameObjectで必要な奴

	//デストラクタ
	virtual ~BulletBase() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//オブジェクトの名前取得処理
	virtual std::string GetName() = 0;

	//オブジェクトの当たり判定取得処理
	virtual const CollisionData& GetCollisionData() = 0;

	//オブジェクトの衝突判定処理
	virtual void OnCollision() = 0;

	//死亡フラグの取得
	virtual const bool GetIsDead() = 0;

	//死亡アニメーションフラグの取得
	virtual const bool GetDeathAnimationFlag() = 0;

	//ロックオン
	virtual void LockOn() = 0;

	virtual const bool GetLockOnFlag() = 0;

public://Bulletで必要な奴
	virtual void SetCamera(Camera* camera) = 0;
	virtual void SetPos(const myMath::Vector3& position) = 0;
	virtual void SetDirectionVector(const myMath::Vector3& directionVector) = 0;
	virtual void SetOwner(BulletOwner owner) = 0;
	virtual void SetName(const std::string& name) = 0;
	virtual void SetTargetPos(const myMath::Vector3& position) = 0;
	virtual void SetControlPos(const myMath::Vector3& position) = 0;
};