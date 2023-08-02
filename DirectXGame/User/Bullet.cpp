#include "Bullet.h"
#include"ColliderManager.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const myMath::Vector3& position, const myMath::Vector3& directionVector, BulletOwner owner)
{
	bullet_ = std::make_unique<Model>();
	bulletTex_ = bullet_->CreateObjModel("Resources/sphere");
	bullet_->SetModel(bulletTex_);
	bulletTrans_.Initialize();
	bulletTrans_.translation = position;
	directionVector_ = directionVector;

	owner_ = owner;

	//�p�[�e�B�N���̏�����
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();
}

void Bullet::Update(Camera* camera)
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
		if (owner_ == BulletOwner::Player)
		{
			ColliderManager::GetInstance()->SubPlayerBullet(this);
		}
		else if (owner_ == BulletOwner::Enemy)
		{
			ColliderManager::GetInstance()->SubEnemyBullet(this);
		}
	}
	bulletTrans_.translation += directionVector_ * speed_;
	bulletTrans_.TransUpdate(camera);

	SmokeUpdate(camera);
}

void Bullet::Draw()
{
	bullet_->DrawModel(&bulletTrans_);
	smokeEmitter_->Draw();
}

void Bullet::SmokeUpdate(Camera* camera)
{
	//�G���W���̍��W�ɍ��킹�邽�߁A���f���̒��S���W����ʒu�����点��悤�Ɏq���쐬
	smokeTrans_.parent = &bulletTrans_;
	//���f���̒��S���W����ʒu�����炷
	smokeTrans_.translation = { 0.0f,0.0f,-1.0f };
	//�q�̍X�V����
	smokeTrans_.TransUpdate(camera);
	//�p�[�e�B�N���𖈃t���[���쐬
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//�p�[�e�B�N���̍X�V
	smokeEmitter_->Update(camera);
}

bool Bullet::GetIsDead()
{
	return isDead_;
}

void Bullet::OnCollision()
{
	isDead_ = true;
}

const myMath::Vector3& Bullet::GetPosition()
{
	return bulletTrans_.translation;
}