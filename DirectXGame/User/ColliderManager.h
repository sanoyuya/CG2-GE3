#pragma once
#include<list>
#include"Collision.h"
#include"Player.h"
#include"EnemyManager.h"
#include <forward_list>

class ColliderManager
{
private:

	std::list<Bullet*>playersBulletsCollider_;
	std::list<Enemy*>enemysCollider_;
	std::list<Bullet*>enemysBulletsCollider_;

public:

	void Update(Player* player);

	void AddPlayerBulletCollider(Bullet* collider);
	void SubPlayerBullet(Bullet* bullet);

	void AddEnemyCollider(Enemy* collider);

	void AddEnemyBulletCollider(Bullet* collider);
	void SubEnemyBullet(Bullet* bullet);

	void Reset();

private:

	void PlayerBulletToEnemy();
	void EnemyBulletToPlayer(Player* player);
	void EnemyToPlayer(Player* player);

public:

	//�V���O���g��
	static ColliderManager* GetInstance();

private:

	ColliderManager() = default;
	~ColliderManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ColliderManager& operator=(const ColliderManager&) = delete;
	ColliderManager(const ColliderManager&) = delete;
};

