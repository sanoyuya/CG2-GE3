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

	const myMath::Vector3 buildingSize_ = { 10.0f,20.0f,10.0f };
	const float backCubeSubSize_ = 0.5f;

	CollisionData collisionData_;

	bool isSet = false;

public:

	Building() = default;
	~Building() {};

	void Initialize()override;

	void Update()override;

	void Draw()override;

	std::string GetName()override;

	const Transform& GetTransform()override;

	//オブジェクトの当たり判定取得処理
	const CollisionData& GetCollisionData()override;

	//オブジェクトの衝突判定処理
	void OnCollision()override {};

	//弾の爆発処理
	void BulletDeathAnimation()override {};

	void LockOn()override {};

	void CancelLockOn()override {};

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	void SetPosition(const myMath::Vector3& position)override;
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	void SetRotation(const myMath::Vector3& rotation)override;
	//blenderで出力したデータを読み込むときにスケールをセットする関数
	void SetScale(const myMath::Vector3& scale)override;
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	void SetColliderSize(const float size)override;
};