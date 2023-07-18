#pragma once
#include"DrawOversight.h"
#include<list>
#include"Player.h"

class Enemy :public Character
{
private:

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	bool isDead_ = false;

	float bulletTimer = 0.0f;
	const float maxBulletTime = 60.0f;

public:

	Enemy();
	~Enemy();

	void Initialize();

	void Update(Camera* camera, Player*player);

	void Draw();

	void SetPosition(const myMath::Vector3& position);

	const myMath::Vector3& GetPosition();

	bool GetIsDead();

	void OnCollision();

private:

	void BulletUpdate(Camera* camera, Player* player);

	void BulletDraw();
};