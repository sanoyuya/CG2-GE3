#pragma once
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"Player.h"
#include"DeathCube.h"

class Enemy
{
private:

	std::unique_ptr<Sprite>enemy;
	Transform enemyTrans;
	uint32_t enemyTex = 0;

	std::unique_ptr<Sprite>exclamation;
	uint32_t exclamationTex = 0;

	myMath::Vector3 enemyVec = { 0,0,0 };
	myMath::Vector3 normEnemyVec = { 0,0,0 };
	float angle = 0.0f;
	float radius = 0.0f;

	bool isDead = false;

	bool animationFlag = false;
	float animationCoolTime = 0.0f;

	bool deathFlag = false;
	float deathTimer = 0.0f;

	std::list<std::unique_ptr<DeathCube>> deathCubes;
	bool generationFlag = false;
	float scale = 1.0f;

public:

	void Initialize(const myMath::Vector3 position);
	void Update(Camera* camera, Player* player);
	void Draw(Camera* camera, myMath::Vector4 color);

	bool GetIsDead();

private:

	void Move(Player* player);
	void DeathAnimation(Camera* camera);
};