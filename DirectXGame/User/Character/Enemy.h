#pragma once
#include"DrawOversight.h"
#include<list>
#include"Player.h"
#include"EnemyDeathParticleEmitter.h"
#include"GameTimer.h"

class Enemy :public GameObject
{
protected:

	Camera* camera_ = nullptr;
	Player* player_ = nullptr;
	GameTimer* gameTimer_ = nullptr;

public:

	virtual ~Enemy() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//オブジェクトの名前取得処理
	virtual std::string GetName() = 0;

	virtual bool GetIsDead() = 0;

public:

	//blenderで出力したデータを読み込むときに初期座標をセットする関数
	virtual void SetPosition(const myMath::Vector3& position) = 0;
	//blenderで出力したデータを読み込むときに初期角度をセットする関数
	virtual void SetRotation(const myMath::Vector3& rotation) = 0;
	//blenderで出力したデータを読み込むときに当たり判定の大きさをセットする関数
	virtual void SetColliderSize(const float size) = 0;
	//blenderで出力したデータを読み込むときにスポーンタイマーをセットする関数
	virtual void SetSpawnTimer(const float timer) = 0;
	//blenderで出力したデータを読み込むときに死亡タイマーをセットする関数
	virtual void SetDeathTimer(const float timer) = 0;

	void SetCamera(Camera* camera);

	void SetPlayer(Player* player);

	void SetGameTimer(GameTimer* gameTimer);

	virtual const Transform& GetTrans() = 0;

	virtual const float& GetColliderSize() = 0;

	virtual bool GetSpawnFlag() = 0;

	virtual bool GetDeathAnimationFlag() = 0;

	virtual void OnCollision() = 0;
};