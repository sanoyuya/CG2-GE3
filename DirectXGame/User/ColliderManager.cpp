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
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerのHP減少
						object2->OnCollision();//敵を消滅させる
					}
				}
			}

			//playerの弾と敵の当たり判定
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemy")
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
	objects.clear();
}

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;
	return &instance;
}