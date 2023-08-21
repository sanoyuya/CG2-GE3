#include "Player.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include<imgui.h>

Player::~Player()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void Player::Initialize()
{
	input_ = InputManager::GetInstance();

	//���e�B�N���̏�����
	reticle_ = std::make_unique<Reticle>();
	reticle_->Initialize();

	//�v���C���[�̏�����
	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,10.0f };
	playerTrans_.scale = { 0.5f,0.5f,0.5f };
	cameraTrans_.Initialize();

	//HP�o�[�̏�����
	hpBar_ = std::make_unique<HPBar>();
	hpBar_->Initialize(maxHp_, { 100.0f,100.0f });

	//�p�[�e�B�N���̏�����
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();

	//���S���o�̏�����
	deathAnimation_ = std::make_unique<PlayerDeathAnimation>();
	deathAnimation_->Initialize();

	collisionData_.radius = 1.0f;

	ColliderManager::GetInstance()->AddCollision(this);
}

void Player::Update()
{
	//�J������e�ɂ���ׂɍs���Transform��matWorld�ɓo�^
	cameraTrans_.matWorld = camera_->GetMatView();
	//���e�B�N���̐e�ɃJ������ݒ�
	playerTrans_.parent = &cameraTrans_;

	//HP�o�[�̍X�V
	hpBar_->Update(hp_);

	if (hp_ <= 0)
	{
		//���S���o�̍X�V����
		deathAnimation_->Update(playerTrans_.parentToTranslation);
	}
	else
	{
		reticle_->SetCamera(camera_);
		//���e�B�N���̍X�V����
		reticle_->Update();
		//���@�̈ړ�����
		Move();
		//���b�N�I���U��
		LockOnAttack();
	}

	//Transform�̍X�V����
	playerTrans_.TransUpdate(camera_);

	collisionData_.center = playerTrans_.parentToTranslation;

	//���[�J���̐��ʃx�N�g��
	directionVector_ = reticle_->GetTransform().translation - playerTrans_.translation;
	//���K��
	directionVector_.normalization();

	//���[���h�̐��ʃx�N�g��
	parentToDirectionVector_ = reticle_->GetTransform().parentToTranslation - playerTrans_.parentToTranslation;
	//���K��
	parentToDirectionVector_.normalization();

	//���@�̉�]����
	Rotation(camera_);

	//�e�̍X�V����
	BulletUpdate();
	//�G���W���̉��̍X�V����
	SmokeUpdate(camera_);
	//���S���o�̃p�[�e�B�N���̍X�V����
	deathAnimation_->ParticleUpdate(camera_);
	//���S���o�Ŏ��S�������Ƃ��̃t���O�̒l��Ⴄ
	deathFlag_ = deathAnimation_->GetDeathFlag();
}

void Player::Draw()
{
	if (hp_ > 0)
	{
		//���e�B�N���̕`��
		reticle_->Draw();
		//�v���C���[�̃��f���`��
		player_->DrawModel(&playerTrans_);
		//�@�̂̃G���W������΂��o��p�[�e�B�N���̕`��
		smokeEmitter_->Draw();
		//HP�o�[�̕`��
		hpBar_->Draw();
	}

	//���S���o�̕`��
	deathAnimation_->Draw();
}

std::string Player::GetName()
{
	return name_;
}

const CollisionData& Player::GetCollisionData()
{
	return collisionData_;
}

void Player::OnCollision()
{
	hp_--;
	hp_ = max(hp_, 0);
	damageFlag_ = true;
}

const bool Player::GetIsDead()
{
	return deathFlag_;
}

const bool Player::GetDeathAnimationFlag()
{
	return deathAnimation_.get();
}

void Player::LockOn()
{
}

const bool Player::GetLockOnFlag()
{
	return lockOnAttackFlag;
}

void Player::Reset()
{
	playerTrans_.translation = { 0.0f,-reticle_->GetReticleLimit() / 9,10.0f };
	hp_ = 10;
	//���e�B�N���̃��Z�b�g
	reticle_->Reset();
	lockOnAttackFlag = false;
}

const bool Player::GetDamageFlag()
{
	return damageFlag_;
}

const Transform& Player::GetTransform()
{
	return playerTrans_;
}

const uint8_t Player::GetHp()
{
	return hp_;
}

void Player::SetDamageFlag(const bool damageFlag)
{
	damageFlag_ = damageFlag;
}

const myMath::Vector3& Player::GetAddTargetPos()
{
	return targetPos;
}

void Player::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void Player::SetBulletManager(BulletManager* bulletManager)
{
	bulletManager_ = bulletManager;
}

void Player::Move()
{
	//��ɕ�Ԑ�̍��W���`����
	float reticleX = reticle_->GetTransform().translation.x / 6;
	float reticleY = reticle_->GetTransform().translation.y / 6;
	//���̂܂܈ړ�������Ɠ������d���̂ŕ⊮����
	PhysicsMath::Complement(playerTrans_.translation.x, reticleX, 30.0f);
	PhysicsMath::Complement(playerTrans_.translation.y, reticleY, 30.0f);
}

void Player::Rotation(Camera* camera)
{
	//���e�B�N���̕����Ɍ����悤�ɉ�]
	playerTrans_.rotation.x = -std::atan2(directionVector_.y, directionVector_.z);
	playerTrans_.rotation.y = -std::atan2(directionVector_.z, directionVector_.x) + myMath::AX_PIF / 2;

	float angleZ = -(reticle_->GetTransform().translation.x / 6 - playerTrans_.translation.x) / 5.0f;
	//���f����Z����]
	PhysicsMath::Complement(playerTrans_.rotation.z, angleZ, 15.0f);

	myMath::Vector3 cameraFrontVec = camera->GetTarget() - camera->GetEye();
	myMath::Vector3 cameraUp =
	{
		sinf(cameraFrontVec.y) * sinf(playerTrans_.rotation.z),
		cosf(cameraFrontVec.y) * cosf(playerTrans_.rotation.z),
		0.0f
	};
	camera->SetUp(cameraUp);

	//�v���C���[�̉������̉�]�����[���h���W�ɕϊ����A��ŃJ�����ɑ�����悤�ɕϐ��Ɋi�[
	targetPos = (playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,1 }) - playerTrans_.matWorld.Transform(playerTrans_.matWorld, { 0,0,0 })) * 0.1f;

	ImGui::Begin("rot");
	ImGui::InputFloat3("playerRot", &playerTrans_.rotation.x);
	ImGui::InputFloat3("cameraFrontVec", &cameraFrontVec.x);
	myMath::Vector3 cameraTarget = camera->GetTarget();
	ImGui::InputFloat3("cameraTarget", &cameraTarget.x);
	myMath::Vector3 cameraPos = camera->GetEye();
	ImGui::InputFloat3("cameraPos", &cameraPos.x);
	ImGui::End();
}

void Player::BulletUpdate()
{
	if (hp_ > 0)
	{
		if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
		{
			//�e�̍쐬
			bulletManager_->CreateNormalBullet(playerTrans_.parentToTranslation, parentToDirectionVector_, BulletOwner::Player);
		}
	}
}

void Player::SmokeUpdate(Camera* camera)
{
	//�G���W���̍��W�ɍ��킹�邽�߁A���f���̒��S���W����ʒu�����点��悤�Ɏq���쐬
	smokeTrans_.parent = &playerTrans_;
	//���f���̒��S���W����ʒu�����炷
	smokeTrans_.translation = { 0.0f,-0.3f,-4.0f };
	//�q�̍X�V����
	smokeTrans_.TransUpdate(camera);
	//�p�[�e�B�N���𖈃t���[���쐬
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//�p�[�e�B�N���̍X�V
	smokeEmitter_->Update(camera);
}

void Player::LockOnAttack()
{
	if (input_->KeyboardKeepPush(DIK_SPACE) || input_->ControllerButtonKeepPush(A))
	{
		lockOnAttackFlag = true;
	}

	if (lockOnAttackFlag == true)
	{
		if (input_->KeyboardTriggerRelease(DIK_SPACE) || input_->ControllerButtonTriggerRelease(A))
		{
			for (auto& lockOnEnemy : ColliderManager::GetInstance()->GetLockOnEnemy())
			{
				myMath::Vector3 controlPoint = { static_cast<float>(myMath::GetRandPlusOrMinus() *myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)),
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)) ,
				static_cast<float>(myMath::GetRandPlusOrMinus() * myMath::GetRand(playerTrans_.parentToTranslation.x + 1.0f,playerTrans_.parentToTranslation.x + 2.0f)) };
				bulletManager_->CreateLockOnBullet(playerTrans_.parentToTranslation, lockOnEnemy->GetCollisionData().center, controlPoint);
			}
			ColliderManager::GetInstance()->ResetLockOnEnemy();
			lockOnAttackFlag = false;
		}
	}
}