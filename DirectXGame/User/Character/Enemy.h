#pragma once
#include"DrawOversight.h"

class Enemy
{
private:

	std::unique_ptr<Model>enemy_;
	uint32_t enemyTex_ = 0;
	Transform enemyTrans_;
	bool isDead_;

public:

	Enemy();
	~Enemy();

	void Initialize();

	void Update(Camera* camera);

	void Draw();

	void SetPosition(const myMath::Vector3& position);

	bool GetIsDead();
};