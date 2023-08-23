#include "ColliderManager.h"

void ColliderManager::Update(Player* player)
{
	objects.remove_if([](GameObject* object) { return object->GetIsDead(); });

	for (auto& object1 : objects)
	{
		for (auto& object2 : objects)
		{
			if (player->GetHp() > 0)
			{
				//playerと敵の弾の当たり判定
				if (object1->GetName() == "player" && object2->GetName() == "enemyBullet")
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerのHP減少
						object2->OnCollision();//敵の弾を消滅させる
					}
				}

				//playerと敵の当たり判定
				if (object1->GetName() == "player" && object2->GetName() == "enemy")
				{
					if (object2->GetDeathAnimationFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//playerのHP減少
							object2->OnCollision();//敵を消滅させる
						}
					}
				}

				//レティクルと敵の当たり判定
				if (object1->GetName() == "reticle" && object2->GetName() == "enemy")
				{
					if (player->GetLockOnFlag() == true && object2->GetDeathAnimationFlag() == false && object2->GetLockOnFlag() == false)
					{
						if (Collision::RayToSphere(object1->GetCollisionData().rayStartPos, object1->GetCollisionData().rayEndPos,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object2->LockOn();//ロックオン
							AddLockOnEnemy(object2);//ロックオン敵listに敵を追加
						}
					}
				}
			}

			//playerの弾と敵の当たり判定
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemy")
			{
				if (object2->GetDeathAnimationFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerの弾を消滅させる
						object2->OnCollision();//敵を消滅させる
					}
				}
			}
		}
	}
}

void ColliderManager::AddCollision(GameObject* object)
{
	objects.push_back(object);
}

void ColliderManager::SubCollision(GameObject* object)
{
	objects.remove(object);
}

void ColliderManager::AddLockOnEnemy(GameObject* lockOnEnemy)
{
	lockOnEnemys.push_back(lockOnEnemy);
}

void ColliderManager::ResetLockOnEnemy()
{
	lockOnEnemys.clear();
}

std::list<GameObject*> ColliderManager::GetLockOnEnemy()
{
	return lockOnEnemys;
}

void ColliderManager::SubLockOnEnemy(GameObject* lockOnEnemy)
{
	lockOnEnemys.remove(lockOnEnemy);
}

void ColliderManager::Reset()
{
	objects.clear();
	lockOnEnemys.clear();
}

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;
	return &instance;
}