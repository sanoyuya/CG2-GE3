#include "Reticle.h"
#include <algorithm>
#include "ColliderManager.h"

void Reticle::Initialize()
{
	input_ = InputManager::GetInstance();

	//�X�v���C�g�̏�����
	reticle_ = std::make_unique<Sprite>();
	reticleTex_ = reticle_->LoadTexture("Resources/reticle.png");
	reticle_->Sprite3DInitialize(reticleTex_);
	reticleTrans_.Initialize();
	reticleTrans_.translation = { 0.0f,-reticleLimit_,30.0f };
	reticleTrans_.scale = { 0.125f,0.125f,1.0f };

	rayStartTrans_.Initialize();
	rayStartTrans_.parent = &reticleTrans_;
	rayStartTrans_.translation = { 0.0f ,0.0f ,-30.0f };
	rayEndTrans_.Initialize();
	rayEndTrans_.parent = &reticleTrans_;
	rayEndTrans_.translation = { 0.0f ,0.0f ,1000.0f };

	ColliderManager::GetInstance()->AddCollision(this);
}

std::string Reticle::GetName()
{
	return name_;
}

const CollisionData& Reticle::GetCollisionData()
{
	return collisionData;
}

void Reticle::OnCollision()
{
}

const bool Reticle::GetIsDead()
{
	return false;
}

void Reticle::Update()
{
	//�J������e�ɂ���ׂɍs���Transform��matWorld�ɓo�^
	cameraTrans_.matWorld = camera_->GetMatView();
	//���e�B�N���̐e�ɃJ������ݒ�
	reticleTrans_.parent = &cameraTrans_;

	//�ړ�����
	Move();
	//�ړ���������
	ReticleLimit();

	//�X�v���C�g�̍X�V����
	reticleTrans_.TransUpdate(camera_);
	rayStartTrans_.TransUpdate(camera_);
	rayEndTrans_.TransUpdate(camera_);

	collisionData.rayStartPos = rayStartTrans_.parentToTranslation;
	collisionData.rayEndPos = rayEndTrans_.parentToTranslation;
}

void Reticle::Draw()
{
	reticle_->DrawSprite3D(camera_, reticleTrans_);
}

const bool Reticle::GetDeathAnimationFlag()
{
	return false;
}

const bool Reticle::GetLockOnFlag()
{
	return false;
}

void Reticle::LockOn()
{
}

void Reticle::Reset()
{
	reticleTrans_.translation = { 0.0f,-reticleLimit_,30.0f };
}

const float Reticle::GetReticleLimit()
{
	return reticleLimit_;
}

const Transform& Reticle::GetTransform()
{
	return reticleTrans_;
}

void Reticle::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void Reticle::Move()
{
#pragma region �L�[�{�[�h
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		reticleTrans_.translation += {0.0f, reticleSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		reticleTrans_.translation += {-reticleSpeed_, 0.0f, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		reticleTrans_.translation += {0.0f, -reticleSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		reticleTrans_.translation += {reticleSpeed_, 0.0f, 0.0f};
	}
#pragma endregion �L�[�{�[�h

#pragma region �R���g���[���[

	//L�X�e�B�b�N���X���邱�Ƃňړ��ł���悤�ɂ���
	reticleTrans_.translation += {reticleSpeed_* input_->GetLeftStickVec().x, -reticleSpeed_ * input_->GetLeftStickVec().y, 0.0f};

#pragma endregion �R���g���[���[
}

void Reticle::ReticleLimit()
{
	reticleTrans_.translation.x = std::clamp(reticleTrans_.translation.x, -reticleLimit_, reticleLimit_);
	//��ʔ䗦�ɍ��킹����������(x:y,16:9)
	reticleTrans_.translation.y = std::clamp(reticleTrans_.translation.y, -reticleLimit_ / 16 * 9, reticleLimit_ / 16 * 9);
}