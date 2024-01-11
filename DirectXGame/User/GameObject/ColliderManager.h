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

	std::forward_list<GameObject*>objects;

	std::list<GameObject*>lockOnEnemys;

	std::forward_list<GameObject*>::iterator itA;
	std::forward_list<GameObject*>::iterator itB;

	bool isCollision_ = true;
	bool isEnemyBulletToPlayer_ = true;
	bool isPlayerToEnemy_ = true;
	bool isPlayerBulletToEnemy_ = true;
	bool isPlayerBulletToEnemyBullet_ = true;
	bool isPlayerToBuilding_ = true;

public:

	void Update(Player* player);

	void AddCollision(GameObject* object);
	void SubCollision(GameObject* object);

	void ResetLockOnEnemy();
	std::list<GameObject*> GetLockOnEnemy();
	void SubLockOnEnemy(GameObject* lockOnEnemy);
	void CancelLockOn();

	void Reset();
	void ImGuiUpdate();

public:

	//シングルトン
	static ColliderManager* GetInstance();

private:

	ColliderManager() = default;
	~ColliderManager() = default;

	void AddLockOnEnemy(GameObject* lockOnEnemy);

	//コピーコンストラクタ・代入演算子削除
	ColliderManager& operator=(const ColliderManager&) = delete;
	ColliderManager(const ColliderManager&) = delete;
};