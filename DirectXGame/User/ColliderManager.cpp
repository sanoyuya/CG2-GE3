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
				//player‚Æ“G‚Ì’e‚Ì“–‚½‚è”»’è
				if (object1->GetName() == "player" && object2->GetName() == "enemyBullet")
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//player‚ÌHPŒ¸­
						object2->OnCollision();//“G‚Ì’e‚ğÁ–Å‚³‚¹‚é
					}
				}

				//player‚Æ“G‚Ì“–‚½‚è”»’è
				if (object1->GetName() == "player" && object2->GetName() == "enemy")
				{
					if (object2->GetDeathAnimationFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//player‚ÌHPŒ¸­
							object2->OnCollision();//“G‚ğÁ–Å‚³‚¹‚é
						}
					}
				}
			}

			//player‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemy")
			{
				if (object2->GetDeathAnimationFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//player‚Ì’e‚ğÁ–Å‚³‚¹‚é
						object2->OnCollision();//“G‚ğÁ–Å‚³‚¹‚é
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

void ColliderManager::Reset()
{
	objects.clear();
}

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;
	return &instance;
}