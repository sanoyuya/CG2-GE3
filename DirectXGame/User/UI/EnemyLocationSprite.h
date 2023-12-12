#pragma once
#include"DrawOversight.h"
#include"EnemyManager.h"
#include<list>
#include"Camera.h"

class EnemyLocationSprite
{
private:

	uint8_t enemyCount_ = 0;

	std::vector<std::unique_ptr<Sprite2D>>sprite_;
	static uint32_t spriteTex_;
	const myMath::Vector2 texSize_ = { 100.0f,100.0f };

public:

	static void LoadAsset();

	void Load(EnemyManager* enemys);

	void ReLoad(EnemyManager* enemys);

	void Initialize();

	void Update();

	void Draw(EnemyManager* enemys, Camera* camera);
};