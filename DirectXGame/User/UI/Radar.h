#pragma once
#include"DrawOversight.h"
#include"EnemyManager.h"
#include"Player.h"
#include"Camera.h"

class Radar
{
private:

	const myMath::Vector2 center_ = { 1130.0f,570.0f };
	const float radarSize = 96.0f;
	const float radarEnemySize = 5.0f;

	std::unique_ptr<Sprite>radar_;
	uint32_t radarTex_ = 0;

	std::unique_ptr<Sprite>player_;
	uint32_t playerTex_ = 0;

	uint32_t enemyTex = 0;
	std::vector<std::unique_ptr<Sprite>>radarEnemys_;

	myMath::Vector3 cameraFrontVec_ = {};

public:

	Radar() = default;
	~Radar() = default;

	void Initialize(EnemyManager* enemys);
	void Update(Camera* camera);
	void Draw(EnemyManager* enemys, Player* player);
};