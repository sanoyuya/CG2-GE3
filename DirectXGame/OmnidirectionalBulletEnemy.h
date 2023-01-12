#pragma once
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include"Player.h"
#include"DeathCube.h"
#include"EnemyBullet.h"

class OmnidirectionalBulletEnemy
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

	float alpha = 0.0f;

	bool deleteFlag = false;

	//�e���X�g
	std::array<std::list<std::unique_ptr<EnemyBullet>>, 8> enemyBullets;
	float coolTime = 0.0f;

public:

	void Initialize(const myMath::Vector3 position);
	void Update(Camera* camera, Player* player);
	void Draw(Camera* camera, myMath::Vector4 color);

	bool GetIsDead();

private:

	void Attack(Player* player, Camera* camera);
	void DeathAnimation(Camera* camera, myMath::Vector4 color);
};