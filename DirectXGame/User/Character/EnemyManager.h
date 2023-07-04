#pragma once
#include"Enemy.h"
#include <list>
#include<memory>

struct EnemyData
{
	std::list<std::unique_ptr<Enemy>>normalEnemys;
};

class EnemyManager
{
private:

	std::list<std::unique_ptr<Enemy>>normalEnemys_;

public:

	EnemyManager();
	~EnemyManager();

	void Initialize(EnemyData& enemyData);

	void Update(Camera* camera);

	void Draw();

	void Load(EnemyData& enemyData);

	void ReLoad(EnemyData& enemyData);

	void Reset();
};