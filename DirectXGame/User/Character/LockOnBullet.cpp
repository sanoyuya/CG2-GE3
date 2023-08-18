#include "LockOnBullet.h"
#include"ColliderManager.h"
#include"EasingFunction.h"

LockOnBullet::~LockOnBullet()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void LockOnBullet::Initialize()
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

void LockOnBullet::Update()
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
	}
	
	BulletMove();

	collisionData_.center = bulletTrans_.translation;

	SmokeUpdate();
}

void LockOnBullet::Draw()
{
	bullet_->DrawModel(&bulletTrans_);
	smokeEmitter_->Draw();
}

std::string LockOnBullet::GetName()
{
	return name_;
}

const CollisionData& LockOnBullet::GetCollisionData()
{
	return collisionData_;
}

void LockOnBullet::OnCollision()
{
	isDead_ = true;
}

const bool LockOnBullet::GetIsDead()
{
	return isDead_;
}

const bool LockOnBullet::GetDeathAnimationFlag()
{
	return false;
}

void LockOnBullet::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void LockOnBullet::SetPos(const myMath::Vector3& position)
{
	bulletTrans_.translation = position;//�O�̂���
	startPos_ = position;
}

void LockOnBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
	directionVector;
}

void LockOnBullet::SetOwner(BulletOwner owner)
{
	owner_ = owner;
}

void LockOnBullet::SetName(const std::string& name)
{
	name_ = name;
}

void LockOnBullet::SetTargetPos(const myMath::Vector3& position)
{
	targetPos_ = position;
}

void LockOnBullet::SetControlPos(const myMath::Vector3& position)
{
	controlPos_ = position;
}

void LockOnBullet::SmokeUpdate()
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

void LockOnBullet::BulletMove()
{
	//�e�̈ړ��Ƀx�W�G��Ԃ�������
	bulletTrans_.translation = myMath::Beziers(startPos_, targetPos_, controlPos_, beziersTime_);

	//�x�W�G��ԂɃC�[�W���O��Ԃ�������
	beziersTime_ = static_cast<float>(Easing::EaseInCirc(deathTimer_, 0.0f, 60.0f, 60.0f));

	bulletTrans_.TransUpdate(camera_);
}