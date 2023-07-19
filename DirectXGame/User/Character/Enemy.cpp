#include "Enemy.h"
#include"ColliderManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/F-35E");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
}

void Enemy::Update(Camera* camera, Player* player)
{
	enemyTrans_.TransUpdate(camera);

	BulletUpdate(camera, player);
}

void Enemy::Draw()
{
	enemy_->DrawModel(&enemyTrans_);

	BulletDraw();
}

void Enemy::SetPosition(const myMath::Vector3& position)
{
	enemyTrans_.translation = position;
}

const myMath::Vector3& Enemy::GetPosition()
{
	return enemyTrans_.translation;
}

bool Enemy::GetIsDead()
{
	return isDead_;
}

void Enemy::OnCollision()
{
	isDead_ = true;
}

void Enemy::BulletUpdate(Camera* camera, Player* player)
{
	myMath::Vector3 frontVec = player->GetTransform().parentToTranslation - enemyTrans_.translation;
	frontVec = frontVec.normalization();

	bulletTimer++;
	if (bulletTimer >maxBulletTime)
	{
		CreateBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);

		bulletTimer = 0.0f;
	}

	//’e‚ÌXVˆ—
	Character::BulletUpdate(camera);
}

void Enemy::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//’e‚Ì•`‰æ
	}
}