#pragma once
#include"Enemy.h"
#include <list>
#include<memory>
#include"Player.h"
#include"GameTimer.h"
#include"NormalEnemy.h"
#include"MoveEnemy.h"

struct EnemyData
{
	std::list<std::unique_ptr<Enemy>>enemys;
};

class EnemyManager
{
private:

	std::list<std::unique_ptr<Enemy>>enemys_;

public:

	EnemyManager();
	~EnemyManager();

	void Initialize(EnemyData& enemyData);

	void Update(Camera* camera,Player* player, GameTimer* gameTimer);

	void Draw();

	void Load(EnemyData& enemyData);

	void ReLoad(EnemyData& enemyData);

	void Reset();

	const std::list<std::unique_ptr<Enemy>>& GetEnemyList();
};