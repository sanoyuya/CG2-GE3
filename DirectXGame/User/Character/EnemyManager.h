#pragma once
#include"Enemy.h"
#include <list>
#include<memory>
#include"Player.h"

struct EnemyData
{
	std::list<std::unique_ptr<Enemy>>normalEnemys;
};

class EnemyManager
{
private:

	std::list<std::unique_ptr<Enemy>>normalEnemys_;
	std::list<Enemy*>list;

public:

	EnemyManager();
	~EnemyManager();

	void Initialize(EnemyData& enemyData);

	void Update(Camera* camera,Player* player);

	void Draw();

	void Load(EnemyData& enemyData);

	void ReLoad(EnemyData& enemyData);

	void Reset();

	const std::list<std::unique_ptr<Enemy>>& GetEnemyList();
};