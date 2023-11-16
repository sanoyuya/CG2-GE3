#pragma once
#include"DrawOversight.h"
#include"BuildingBase.h"

class Building:public BuildingBase
{
private:

	std::string name_ = "building";

	std::unique_ptr<Model>builing_;
	uint32_t buildingTex_ = 0;
	Transform buildingTrans_;

	std::unique_ptr<Model>buildingBack_;
	uint32_t buildingBackTex_ = 0;
	Transform buildingBackTrans_;

	CollisionData collisionData_;

public:

	Building() = default;
	~Building();

	void Initialize();

	void Update();

	void Draw();

	std::string GetName();

	const Transform& GetTransform();

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData();

	//オブジェクトの衝突判定処理
	void OnCollision();

	//弾の爆発処理
	void BulletDeathAnimation();

	void LockOn();

	void CancelLockOn();

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	void SetPosition(const myMath::Vector3& position);
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	void SetRotation(const myMath::Vector3& rotation);
	//blenderで出力したデータを読み込むときにスケールをセットする関数
	void SetScale(const myMath::Vector3& scale);
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	void SetColliderSize(const float size);
};