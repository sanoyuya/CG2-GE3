#pragma once
#include"Enemy.h"
#include <list>
#include<memory>
#include"Player.h"
#include"GameTimer.h"
#include"NormalEnemy.h"
#include"MoveEnemy.h"

struct EnemyList
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

	void Initialize(EnemyList& enemyData);

	void Update(Camera* camera,Player* player, GameTimer* gameTimer, BulletManager* bulletManager);

	void Draw();

	void Load(EnemyList& enemyData);

	void ReLoad(EnemyList& enemyData);

	void Reset();

	const std::list<std::unique_ptr<Enemy>>& GetEnemyList();
};