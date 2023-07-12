#include "Player.h"
#include <algorithm>
#include"PhysicsMath.h"
#include"ColliderManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	input_ = InputManager::GetInstance();

	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
	playerTrans_.translation = { 0.0f,0.0f,10.0f };
	playerTrans_.scale = { 0.5f,0.5f,0.5f };
	cameraTrans_.Initialize();

	reticle_ = std::make_unique<Sprite>();
	reticleTex_ = reticle_->LoadTexture("Resources/reticle.png");
	reticle_->Sprite3DInitialize(reticleTex_);
	reticleTrans_.Initialize();
	reticleTrans_.translation = { 0.0f,0.0f,30.0f };
	reticleTrans_.scale = { 0.125f,0.125f,1.0f };
}

void Player::Update(Camera* camera)
{
	cameraTrans_.matWorld = camera->GetMatView();
	playerTrans_.parent = &cameraTrans_;
	reticleTrans_.parent = &cameraTrans_;

	MoveLimit();
	ReticleMove();
	Move();
	ReticleLimit();

	playerTrans_.TransUpdate(camera);
	reticleTrans_.TransUpdate(camera);

	directionVector_ = reticleTrans_.translation - playerTrans_.translation;//ê≥ñ ÉxÉNÉgÉã
	directionVector_ = directionVector_.normalization();//ê≥ãKâª

	parentToDirectionVector_ = reticleTrans_.parentToTranslation - playerTrans_.parentToTranslation;//ê≥ñ ÉxÉNÉgÉã
	parentToDirectionVector_ = parentToDirectionVector_.normalization();//ê≥ãKâª

	Rotation();

	BulletUpdate(camera);
}

void Player::Draw(Camera* camera)
{
	reticle_->DrawSprite3D(camera, reticleTrans_);
	BulletDraw();
	player_->DrawModel(&playerTrans_);
}

void Player::Reset()
{
	playerTrans_.translation = { 0.0f,0.0f,10.0f };
	reticleTrans_.translation = { 0.0f,0.0f,30.0f };
}

void Player::HpSub()
{
	hp_--;
	damageFlag_ = true;
}

const bool& Player::GetDamageFlag()
{
	return damageFlag_;
}

const Transform& Player::GetTransform()
{
	return playerTrans_;
}

const uint8_t& Player::GetHp()
{
	return hp_;
}

void Player::SetDamageFlag(const bool& damageFlag)
{
	damageFlag_ = damageFlag;
}

void Player::Move()
{
	float reticleX = reticleTrans_.translation.x / 3;
	float reticleY = reticleTrans_.translation.y / 3;
	PhysicsMath::Complement(playerTrans_.translation.x, reticleX, 15.0f);
	PhysicsMath::Complement(playerTrans_.translation.y, reticleY, 15.0f);
}

void Player::Rotation()
{
	playerTrans_.rotation.x = -std::atan2(directionVector_.y, directionVector_.z);
	playerTrans_.rotation.y = -std::atan2(directionVector_.z, directionVector_.x) + myMath::AX_PIF / 2;

	float angleZ = -(reticleTrans_.translation.x / 3 - playerTrans_.translation.x) / 2;
	playerTrans_.rotation.z = PhysicsMath::Complement(playerTrans_.rotation.z, angleZ, 10.0f);
}

void Player::ReticleMove()
{
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
}

void Player::MoveLimit()
{
	playerTrans_.translation.x = std::clamp(playerTrans_.translation.x, -moveLimit, moveLimit);
	playerTrans_.translation.y = std::clamp(playerTrans_.translation.y, -moveLimit / 16 * 9, moveLimit / 16 * 9);
}

void Player::ReticleLimit()
{
	reticleTrans_.translation.x = std::clamp(reticleTrans_.translation.x, -moveLimit * 3, moveLimit * 3);
	reticleTrans_.translation.y = std::clamp(reticleTrans_.translation.y, -moveLimit * 3 / 16 * 9, moveLimit * 3 / 16 * 9);
}

void Player::BulletUpdate(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->GetIsDead(); });

	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		//íeÇê∂ê¨ÇµÅAèâä˙âª
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(playerTrans_.parentToTranslation, parentToDirectionVector_, BulletOwner::Player);
		//íeÇìoò^Ç∑ÇÈ
		ColliderManager::GetInstance()->AddPlayerBulletCollider(newBullet.get());
		bullets_.push_back(std::move(newBullet));
	}

	//íeÇÃçXêVèàóù
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Update(camera);
	}
}

void Player::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//íeÇÃï`âÊ
	}
}