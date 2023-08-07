#pragma once
#include"Bullet.h"
#include"Camera.h"

//オブジェクト基底クラス
class GameObject
{
protected:

	std::list<std::unique_ptr<Bullet>>bullets_;

public:

	virtual ~GameObject() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//オブジェクトの名前取得処理
	virtual std::string GetName() = 0;

	void CreateBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner);
	void BulletUpdate(Camera* camera);
};