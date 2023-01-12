#pragma once
#include"myMath.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Camera.h"
#include "Player.h"

class EnemyBullet
{
private:

	std::unique_ptr<Sprite>enemyBullet;
	Transform enemyBulletTrans;
	uint32_t enemyBulletTex;

	float radius = 0.0f;

	bool isDead = false;

public:

	void Initialize(const myMath::Vector3 position);
	void Update(Player* player, Camera* camera,const myMath::Vector3 normVec);
	void Draw(Camera* camera, myMath::Vector4 color);
	void Move(const myMath::Vector3 normVec);
	
	const bool& GetIsDead();
};