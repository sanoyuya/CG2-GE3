#include "ColliderManager.h"

void ColliderManager::Update(Player* player)
{
	enemysBulletsCollider_.remove_if([](Bullet* bullet) { return bullet->GetIsDead(); });
	playersBulletsCollider_.remove_if([](Bullet* bullet) { return bullet->GetIsDead(); });
	enemysCollider_.remove_if([](Enemy* enemy) { return enemy->GetIsDead(); });

	EnemyBulletToPlayer(player);
	PlayerBulletToEnemy();
	EnemyToPlayer(player);
}

void ColliderManager::AddPlayerBulletCollider(Bullet* collider)
{
	playersBulletsCollider_.push_back(collider);
}

void ColliderManager::SubPlayerBullet(Bullet* bullet)
{
	playersBulletsCollider_.remove(bullet);
}

void ColliderManager::AddEnemyCollider(Enemy* collider)
{
	enemysCollider_.push_back(collider);
}

void ColliderManager::AddEnemyBulletCollider(Bullet* collider)
{
	enemysBulletsCollider_.push_back(collider);
}

void ColliderManager::SubEnemyBullet(Bullet* bullet)
{
	enemysBulletsCollider_.remove(bullet);
}

void ColliderManager::AddCollision(GameObject* object)
{
	objects.push_back(object);
}

void ColliderManager::SubCollision(GameObject* object)
{
	objects.remove(object);
}

void ColliderManager::Reset()
{
	playersBulletsCollider_.clear();
	enemysCollider_.clear();
	enemysBulletsCollider_.clear();
}

void ColliderManager::PlayerBulletToEnemy()
{
	for (auto& bullet : playersBulletsCollider_)
	{
		for (auto& enemys : enemysCollider_)
		{
			if (Collision::SphereToSphere(bullet->GetPosition(),1.0f, enemys->GetPosition(),2.0f))
			{
				bullet->OnCollision();
				enemys->OnCollision();
			}
		}
	}
}

void ColliderManager::EnemyBulletToPlayer(Player* player)
{
	for (auto& bullet : enemysBulletsCollider_)
	{
		if (Collision::SphereToSphere(player->GetTransform().parentToTranslation, 1.0f, bullet->GetPosition(), 1.0f))
		{
			player->HpSub();
			bullet->OnCollision();
		}
	}
}

void ColliderManager::EnemyToPlayer(Player* player)
{
	for (auto& enemys : enemysCollider_)
	{
		if (Collision::SphereToSphere(player->GetTransform().parentToTranslation, 1.0f, enemys->GetPosition(), 2.0f))
		{
			player->HpSub();
			enemys->OnCollision();
		}
	}
}

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;
	return &instance;
}