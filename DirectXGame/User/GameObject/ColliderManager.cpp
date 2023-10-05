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
				//player�ƓG�̒e�̓����蔻��
				if (object1->GetName() == "player" && object2->GetName() == "enemyBullet")
				{
					if (object2->GetDeathFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//player��HP����
							object2->OnCollision();//�G�̒e�����ł�����
						}
					}
				}

				//player�ƓG�̓����蔻��
				if (object1->GetName() == "player" && object2->GetName() == "enemy")
				{
					if (object2->GetDeathAnimationFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//player��HP����
							object2->OnCollision();//�G�����ł�����
						}
					}
				}

				//���e�B�N���ƓG�̓����蔻��
				if (object1->GetName() == "reticle" && object2->GetName() == "enemy")
				{
					if (player->GetLockOnFlag() == true && object2->GetDeathAnimationFlag() == false && object2->GetLockOnFlag() == false)
					{
						if (Collision::RayToSphere(object1->GetCollisionData().rayStartPos, object1->GetCollisionData().rayEndPos,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object2->LockOn();//���b�N�I��
							AddLockOnEnemy(object2);//���b�N�I���Glist�ɓG��ǉ�
						}
					}
				}
			}

			//player�̒e�ƓG�̓����蔻��
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemy")
			{
				if (object2->GetDeathAnimationFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//player�̒e�����ł�����
						object2->OnCollision();//�G�����ł�����
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
						object1->OnCollision();//player�̒e�����ł�����
						object2->OnCollision();//�G�����ł�����
					}
				}
			}

			//player�̒e�ƓG�̒e�̓����蔻��
			if (object1->GetName() == "playerBullet" && object2->GetName() == "enemyBullet")
			{
				if (object2->GetDeathAnimationFlag() == false&& object2->GetDeathFlag() == false)
				{
					if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
						object2->GetCollisionData().center, object2->GetCollisionData().radius))
					{
						object1->OnCollision();//player�̒e�����ł�����
						object2->BulletDeathAnimation();//�G�̒e�����ł�����
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