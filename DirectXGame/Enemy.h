#pragma once
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"Player.h"

class Enemy
{
private:

	std::unique_ptr<Sprite>enemy;
	Transform enemyTrans;
	static uint32_t enemyTex;

	myMath::Vector3 enemyVec = { 0,0,0 };
	myMath::Vector3 normEnemyVec = { 0,0,0 };
	float angle = 0.0f;
	float radius = 0.0f;

	float deathTimer = 0.0f;
	bool isDead = false;

public:

	static const void LoadTexture(uint32_t& texture);
	void Initialize(const myMath::Vector3 position);
	void Update(Camera* camera, Player* player);
	void Draw(Camera* camera);

	bool GetIsDead();

private:

	void Move(Player* player);
};