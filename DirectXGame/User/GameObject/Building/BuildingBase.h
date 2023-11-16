#pragma once
#include"DrawOversight.h"
#include<list>
#include"GameTimer.h"
#include"Transform.h"
#include"GameObject.h"

class BuildingBase :public GameObject
{
protected:

	static Camera* sCamera_;
	static GameTimer* sGameTimer_;

public:

	static void StaticInitialize();

public:

	virtual ~BuildingBase() = default;

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
	virtual void BulletDeathAnimation() = 0;

	virtual void LockOn() = 0;

	virtual void CancelLockOn() = 0;

	static void SetCamera(Camera* camera);

	static void SetGameTimer(GameTimer* gameTimer);

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	virtual void SetPosition(const myMath::Vector3& position) = 0;
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	virtual void SetRotation(const myMath::Vector3& rotation) = 0;
	//blenderで出力したデータを読み込むときにスケールをセットする関数
	virtual void SetScale(const myMath::Vector3& scale) = 0;
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	virtual void SetColliderSize(const float size) = 0;
};