#include "BulletManager.h"
#include"ColliderManager.h"

void BulletManager::CreateBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner)
{
	//’e‚ğ¶¬‚µA‰Šú‰»
	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
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

void BulletManager::BulletUpdate(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->GetIsDead(); });

	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->SetCamera(camera);
		bullet->Update();
	}
}
