#pragma once
#include<list>
#include"Collision.h"
#include"Player.h"
#include"EnemyManager.h"

class ColliderManager
{
private:

	std::list<std::unique_ptr<Bullet>>playerBullets_;
	std::list<std::unique_ptr<Enemy>>enemys_;
	std::list<std::unique_ptr<Bullet>>enemyBullets_;

public:

	void Update(Player* player);

private:

	void PlayerBulletToEnemy();
	void EnemyBulletToPlayer(Player* player);

public:

	void SetPlayerBulletList(std::list<std::unique_ptr<Bullet>>& playerBullets);

	void SetEnemyList(std::list<std::unique_ptr<Enemy>>& enemys);

	void SetEnemyBulletList(std::list<std::unique_ptr<Bullet>>& enemyBullets);

	//�V���O���g��
	static ColliderManager* GetInstance();

private:

	ColliderManager() = default;
	~ColliderManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ColliderManager& operator=(const ColliderManager&) = delete;
	ColliderManager(const ColliderManager&) = delete;
};

