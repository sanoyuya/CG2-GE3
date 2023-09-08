#include "BulletManager.h"
#include"ColliderManager.h"
#include"LockOnBullet.h"

void BulletManager::Update(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<BulletBase>& bullet) { return bullet->GetIsDead(); });

	for (const std::unique_ptr<BulletBase>& bullet : bullets_)
	{
		bullet->SetCamera(camera);
		bullet->Update();
	}
}

void BulletManager::Draw()
{
	for (const std::unique_ptr<BulletBase>& bullet : bullets_)
	{
		bullet->Draw();
	}
}

void BulletManager::CreateNormalBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner)
{
	//’e‚ğ¶¬‚µA‰Šú‰»
	std::unique_ptr<BulletBase> newBullet = std::make_unique<NormalBullet>();
	newBullet->SetPos(position);
	newBullet->SetDirectionVector(frontVec);
	newBullet->SetOwner(owner);
	if (owner == BulletOwner::Player)
	{
		newBullet->SetName("playerBullet");
	}
	else if (owner == BulletOwner::Enemy)
	{
		newBullet->SetName("enemyBullet");
	}
	newBullet->Initialize();

	//’e‚ğ“o˜^‚·‚é
	ColliderManager::GetInstance()->AddCollision(newBullet.get());
	bullets_.push_back(std::move(newBullet));
}

void BulletManager::CreateLockOnBullet(myMath::Vector3 startPos, GameObject* lockOnEnemy, myMath::Vector3 controlPos)
{
	//’e‚ğ¶¬‚µA‰Šú‰»
	std::unique_ptr<BulletBase> newBullet = std::make_unique<LockOnBullet>();
	newBullet->SetPos(startPos);
	newBullet->SetControlPos(controlPos);
	newBullet->SetTargetPos(lockOnEnemy);
	newBullet->Initialize();

	//’e‚ğ“o˜^‚·‚é
	ColliderManager::GetInstance()->AddCollision(newBullet.get());
	bullets_.push_back(std::move(newBullet));
}

void BulletManager::Reset()
{
	bullets_.clear();
}