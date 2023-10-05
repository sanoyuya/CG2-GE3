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
				//playerÇ∆ìGÇÃíeÇÃìñÇΩÇËîªíË
				if (object1->GetName() == "player" && object2->GetName() == "enemyBullet")
				{
					if (object2->GetDeathFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//playerÇÃHPå∏è≠
							object2->OnCollision();//ìGÇÃíeÇè¡ñ≈Ç≥ÇπÇÈ
						}
					}
				}

				//playerÇ∆ìGÇÃìñÇΩÇËîªíË
				if (object1->GetName() == "player" && object2->GetName() == "enemy")
				{
					if (object2->GetDeathAnimationFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//playerÇÃHPå∏è≠
							object2->OnCollision();//ìGÇè¡ñ≈Ç≥ÇπÇÈ
						}
					}
				}

				//ÉåÉeÉBÉNÉãÇ∆ìGÇÃìñÇΩÇËîªíË
				if (object1->GetName() == "reticle" && object2->GetName() == "enemy")
				{
					if (player->GetLockOnFlag() == true && object2->GetDeathAnimationFlag() == false && object2->GetLockOnFlag() == false)
					{
						if (Collision::RayToSphere(object1->GetCollisionData().rayStartPos, object1->GetCollisionData().rayEndPos,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object2->LockOn();//ÉçÉbÉNÉIÉì
							AddLockOnEnemy(object2);//ÉçÉbÉNÉIÉììGlistÇ…ìGÇí«â¡
						}
					}
				}
			}

			//playerÇÃíeÇ∆ìGÇÃìñÇΩÇËîªíË
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemy")
			{
				if (object2->GetDeathAnimationFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerÇÃíeÇè¡ñ≈Ç≥ÇπÇÈ
						object2->OnCollision();//ìGÇè¡ñ≈Ç≥ÇπÇÈ
					}
				}
			}

			if (object1->GetName() == "lockOnBullet" && object2->GetName() == "enemy")
			{
				if (object2->GetDeathAnimationFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerÇÃíeÇè¡ñ≈Ç≥ÇπÇÈ
						object2->OnCollision();//ìGÇè¡ñ≈Ç≥ÇπÇÈ
					}
				}
			}

			//playerÇÃíeÇ∆ìGÇÃíeÇÃìñÇΩÇËîªíË
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemyBullet")
			{
				if (object2->GetDeathAnimationFlag() == false&& object2->GetDeathFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//playerÇÃíeÇè¡ñ≈Ç≥ÇπÇÈ
						object2->BulletDeathAnimation();//ìGÇÃíeÇè¡ñ≈Ç≥ÇπÇÈ
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

void ColliderManager::CancelLockOn()
{
	for (auto& object : objects)
	{
		if (object->GetName() == "enemy")
		{
			object->CancelLockOn();
		}
	}
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