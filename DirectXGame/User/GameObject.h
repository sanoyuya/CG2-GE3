#pragma once

struct CollisionData
{
	myMath::Vector3 center = {};
	float radius = 0.0f;
};

//オブジェクト基底クラス
class GameObject
{
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

	//オブジェクトの当たり判定取得処理
	virtual const CollisionData& GetCollisionData() = 0;

	//オブジェクトの衝突判定処理
	virtual void OnCollision() = 0;

	//死亡フラグの取得
	virtual const bool GetIsDead() = 0;

	//死亡アニメーションフラグの取得
	virtual const bool GetDeathAnimationFlag() = 0;
};