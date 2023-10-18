#include "ColliderManager.h"
#include<imgui.h>

void ColliderManager::Update(Player* player)
{
	objects.remove_if([](GameObject* object) { return object->GetIsDead(); });

	for (auto& object1 : objects)
	{
		for (auto& object2 : objects)
		{
			if (player->GetHp() > 0)
			{
#ifdef _DEBUG
				if (isEnemyBulletToPlayer_==true)
#endif _DEBUG
				{
					//playerと敵の弾の当たり判定
					if (object1->GetName() == "player" && object2->GetName() == "enemyBullet")
					{
						if (object2->GetDeathFlag() == false)
						{
							if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
								object2->GetCollisionData().center, object2->GetCollisionData().radius))
							{
								object1->OnCollision();//playerのHP減少
								object2->OnCollision();//敵の弾を消滅させる
							}
						}
					}
				}

#ifdef _DEBUG
				if (isPlayerToEnemy_ == true)
#endif _DEBUG
				{
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

#ifdef _DEBUG
			if (isPlayerBulletToEnemy_ == true)
#endif _DEBUG
			{
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

				if (object1->GetName() == "lockOnBullet" && object2->GetName() == "enemy")
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

#ifdef _DEBUG
			if (isPlayerBulletToEnemyBullet_ == true)
#endif _DEBUG
			{
				//playerの弾と敵の弾の当たり判定
				if (object1->GetName() == "playerBullet" && object2->GetName() == "enemyBullet")
				{
					if (object2->GetDeathAnimationFlag() == false && object2->GetDeathFlag() == false)
					{
						if (Collision::SphereToSphere(object1->GetCollisionData().center, object1->GetCollisionData().radius,
							object2->GetCollisionData().center, object2->GetCollisionData().radius))
						{
							object1->OnCollision();//playerの弾を消滅させる
							object2->BulletDeathAnimation();//敵の弾を消滅させる
						}
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

void ColliderManager::ImGuiUpdate()
{
	ImGui::Begin("Collider");
	ImGui::Checkbox("isEnemyBulletToPlayer", &isEnemyBulletToPlayer_);
	ImGui::Checkbox("isPlayerToEnemy_", &isPlayerToEnemy_);
	ImGui::Checkbox("isPlayerBulletToEnemy_", &isPlayerBulletToEnemy_);
	ImGui::Checkbox("isPlayerBulletToEnemyBullet_", &isPlayerBulletToEnemyBullet_);
	ImGui::End();
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