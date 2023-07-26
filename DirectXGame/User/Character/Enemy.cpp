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

	// ƒp[ƒeƒBƒNƒ‹¶¬
	emitter_ = std::make_unique<EnemyParticleEmitter>();
	emitter_->Initialize();
}

void Enemy::Update(Camera* camera, Player* player)
{
	//“G‚Ìƒ‚ƒfƒ‹‚ÌXVˆ—
	enemyTrans_.TransUpdate(camera);
	//’e‚Ì¶¬ˆ—‚ÆXVˆ—
	BulletUpdate(camera, player);

	//€–S‰‰o‚ÌXVˆ—
	if (deathAnimationFlag_ == true)
	{
		emitter_->Update(camera);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		isDead_ = true;
	}
}

void Enemy::Draw()
{
	//€‚ñ‚Å‚¢‚È‚¢‚Æ‚«‚Ì‚İ•`‰æ
	if (deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
	}
	else
	{
		//€–S‰‰o‚Ì•`‰æˆ—
		emitter_->Draw();
	}

	//’e‚Ì•`‰æˆ—
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

bool Enemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void Enemy::OnCollision()
{
	deathAnimationFlag_ = true;
	emitter_->Create(enemyTrans_.parentToTranslation);
}

void Enemy::BulletUpdate(Camera* camera, Player* player)
{
	myMath::Vector3 frontVec = player->GetTransform().parentToTranslation - enemyTrans_.translation;
	frontVec = frontVec.normalization();

	if (deathAnimationFlag_ == false)
	{
		bulletTimer++;
		if (bulletTimer > maxBulletTime)
		{
			CreateBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);

			bulletTimer = 0.0f;
		}
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