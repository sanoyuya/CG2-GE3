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

	std::vector<GameObject*>lockOnEnemys;

public:

	void Update(Player* player);

	void AddCollision(GameObject* object);
	void SubCollision(GameObject* object);

	void ResetLockOnEnemy();
	std::vector<GameObject*> GetLockOnEnemy();

	void Reset();

public:

	//�V���O���g��
	static ColliderManager* GetInstance();

private:

	ColliderManager() = default;
	~ColliderManager() = default;

	void AddLockOnEnemy(GameObject* lockOnEnemy);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ColliderManager& operator=(const ColliderManager&) = delete;
	ColliderManager(const ColliderManager&) = delete;
};