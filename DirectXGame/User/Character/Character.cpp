#include "Character.h"
#include"ColliderManager.h"

void Character::CreateBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner)
{
	//’e‚ğ¶¬‚µA‰Šú‰»
	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
	newBullet->Initialize(position, frontVec, owner);
	//’e‚ğ“o˜^‚·‚é
	if (owner == BulletOwner::Player)
	{
		ColliderManager::GetInstance()->AddPlayerBulletCollider(newBullet.get());
	}
	else if (owner == BulletOwner::Enemy)
	{
		ColliderManager::GetInstance()->AddEnemyBulletCollider(newBullet.get());
	}
	bullets_.push_back(std::move(newBullet));
}

void Character::BulletUpdate(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->GetIsDead(); });

	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Update(camera);
	}
}
