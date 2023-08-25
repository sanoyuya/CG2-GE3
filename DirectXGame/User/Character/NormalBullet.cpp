#include "NormalBullet.h"
#include"ColliderManager.h"

NormalBullet::~NormalBullet()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void NormalBullet::Initialize()
{
	bullet_ = std::make_unique<Model>();
	bulletTex_ = bullet_->CreateObjModel("Resources/sphere");
	bullet_->SetModel(bulletTex_);
	bulletTrans_.Initialize();

	//�p�[�e�B�N���̏�����
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();

	collisionData_.radius = 1.0f;
}

void NormalBullet::Update()
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
	}
	bulletTrans_.translation += directionVector_ * speed_;
	bulletTrans_.TransUpdate(camera_);

	collisionData_.center = bulletTrans_.translation;

	SmokeUpdate();
}

void NormalBullet::Draw()
{
	bullet_->DrawModel(&bulletTrans_);
	smokeEmitter_->Draw();
}

std::string NormalBullet::GetName()
{
	return name_;
}

const CollisionData& NormalBullet::GetCollisionData()
{
	return collisionData_;
}

void NormalBullet::OnCollision()
{
	isDead_ = true;
}

const bool NormalBullet::GetIsDead()
{
	return isDead_;
}

const bool NormalBullet::GetDeathAnimationFlag()
{
	return false;
}

void NormalBullet::LockOn()
{
}

void NormalBullet::CancelLockOn()
{
}

const bool NormalBullet::GetLockOnFlag()
{
	return false;
}

void NormalBullet::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void NormalBullet::SetPos(const myMath::Vector3& position)
{
	bulletTrans_.translation = position;
}

void NormalBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
	directionVector_ = directionVector;
}

void NormalBullet::SetOwner(BulletOwner owner)
{
	owner_ = owner;
}

void NormalBullet::SetName(const std::string& name)
{
	name_ = name;
}

void NormalBullet::SetTargetPos(const myMath::Vector3& position)
{
	position;
}

void NormalBullet::SetControlPos(const myMath::Vector3& position)
{
	position;
}

void NormalBullet::SmokeUpdate()
{
	//�G���W���̍��W�ɍ��킹�邽�߁A���f���̒��S���W����ʒu�����点��悤�Ɏq���쐬
	smokeTrans_.parent = &bulletTrans_;
	//���f���̒��S���W����ʒu�����炷
	smokeTrans_.translation = { 0.0f,0.0f,-1.0f };
	//�q�̍X�V����
	smokeTrans_.TransUpdate(camera_);
	//�p�[�e�B�N���𖈃t���[���쐬
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//�p�[�e�B�N���̍X�V
	smokeEmitter_->Update(camera_);
}