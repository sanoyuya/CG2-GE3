#include "BulletManager.h"
#include"ColliderManager.h"

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
	//íeÇê∂ê¨ÇµÅAèâä˙âª
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

	//íeÇìoò^Ç∑ÇÈ
	ColliderManager::GetInstance()->AddCollision(newBullet.get());
	bullets_.push_back(std::move(newBullet));
}