#include "BulletManager.h"
#include"ColliderManager.h"
#include"LockOnBullet.h"
#include"AudioManager.h"
#include"BulletBase.h"

void BulletManager::Initialize()
{
	sound_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/bullet.mp3", 0.1f);
}

void BulletManager::Update(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<BulletBase>& bullet) { return bullet->GetIsDead(); });

	for (const std::unique_ptr<BulletBase>& bullet : bullets_)
	{
		bullet->Update();
	}
	BulletBase::EmitterUpdate(camera);
}

void BulletManager::Draw()
{
	for (const std::unique_ptr<BulletBase>& bullet : bullets_)
	{
		bullet->Draw();
	}
	BulletBase::EmitterDraw();
}

void BulletManager::CreateNormalBullet(myMath::Vector3 position, myMath::Vector3 frontVec, BulletOwner owner)
{
	//弾を生成し、初期化
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

	//弾を登録する
	ColliderManager::GetInstance()->AddCollision(newBullet.get());
	bullets_.push_back(std::move(newBullet));
}

void BulletManager::CreateLockOnBullet(myMath::Vector3 startPos, GameObject* lockOnEnemy, myMath::Vector3 controlPos)
{
	//弾を生成し、初期化
	std::unique_ptr<BulletBase> newBullet = std::make_unique<LockOnBullet>();
	newBullet->SetPos(startPos);
	newBullet->SetControlPos(controlPos);
	newBullet->SetTargetPos(lockOnEnemy);
	newBullet->Initialize();

	//弾を登録する
	ColliderManager::GetInstance()->AddCollision(newBullet.get());
	bullets_.push_back(std::move(newBullet));

	AudioManager::GetInstance()->PlayWave(sound_, false);
}

void BulletManager::Reset()
{
	bullets_.clear();
}