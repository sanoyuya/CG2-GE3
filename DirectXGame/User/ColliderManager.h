#pragma once
#include<list>
#include"Collision.h"
#include"Player.h"
#include"EnemyManager.h"
#include <forward_list>
#include"GameObject.h"

class ColliderManager
{
private:

	std::list<GameObject*>objects;

public:

	void Update(Player* player);

	void AddCollision(GameObject* object);
	void SubCollision(GameObject* object);

	void Reset();

public:

	//シングルトン
	static ColliderManager* GetInstance();

private:

	ColliderManager() = default;
	~ColliderManager() = default;

	//コピーコンストラクタ・代入演算子削除
	ColliderManager& operator=(const ColliderManager&) = delete;
	ColliderManager(const ColliderManager&) = delete;
};