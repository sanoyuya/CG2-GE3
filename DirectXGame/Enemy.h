#pragma once
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"

class Enemy
{
private:

	std::unique_ptr<DrawOversight>enemy;
	Transform enemyTrans;
	static uint32_t enemyTex;

	myMath::Vector3 enemyVec = { 0,0,0 };
	myMath::Vector3 normEnemyVec = { 0,0,0 };
	float angle = 0.0f;

	bool isDead = false;

public:

	static const void LoadTexture(uint32_t& texture);
	void Initialize(const myMath::Vector3 position);
	void Update(Camera* camera);
	void Draw();

	bool GetIsDead();

private:

	void Move();
	void Attack();
};