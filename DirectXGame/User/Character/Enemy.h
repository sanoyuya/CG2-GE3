#pragma once
#include"DrawOversight.h"
#include"Bullet.h"
#include<list>

class Enemy
{
private:

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	bool isDead_;

	std::list<std::unique_ptr<Bullet>>bullets_;

public:

	Enemy();
	~Enemy();

	void Initialize();

	void Update(Camera* camera);

	void Draw();

	void SetPosition(const myMath::Vector3& position);

	bool GetIsDead();
};