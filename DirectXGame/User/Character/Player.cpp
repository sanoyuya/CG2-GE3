#include "Player.h"
#include <algorithm>

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
	playerTrans_.translation = { 0.0f,-3.0f,10.0f };
	playerTrans_.scale = { 0.5f,0.5f,0.5f };
	cameraTrans_.Initialize();

	reticle_ = std::make_unique<Sprite>();
	reticleTex_ = reticle_->LoadTexture("Resources/reticle.png");
	reticle_->Sprite3DInitialize(reticleTex_);
	reticleTrans_.Initialize();
	reticleTrans_.translation = { 0.0f,0.0f,30.0f };
	reticleTrans_.scale = { 0.125f,0.125f,1.0f};
}

void Player::Update(Camera* camera)
{
	cameraTrans_.matWorld = camera->GetMatView();
	playerTrans_.parent = &cameraTrans_;
	reticleTrans_.parent = &cameraTrans_;

	Move();
	MoveLimit();
	ReticleMove();
	ReticleLimit();

	playerTrans_.TransUpdate(camera);
	reticleTrans_.TransUpdate(camera);

	directionVector_ = reticleTrans_.parentToTranslation - playerTrans_.parentToTranslation;//³–ÊƒxƒNƒgƒ‹
	directionVector_ = directionVector_.normalization();//³‹K‰»

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
}

void Player::Move()
{
	if (input_->KeyboardKeepPush(DIK_W))
	{
		playerTrans_.translation += {0.0f, moveSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_A))
	{
		playerTrans_.translation += {-moveSpeed_, 0.0f, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_S))
	{
		playerTrans_.translation += {0.0f, -moveSpeed_, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_D))
	{
		playerTrans_.translation += {moveSpeed_, 0.0f, 0.0f};
	}
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
	playerTrans_.translation.x = std::clamp(playerTrans_.translation.x, -6.0f, 6.0f);
	playerTrans_.translation.y = std::clamp(playerTrans_.translation.y, -3.0f, 3.0f);
}

void Player::ReticleLimit()
{
	reticleTrans_.translation.x = std::clamp(reticleTrans_.translation.x, -25.0f, 25.0f);
	reticleTrans_.translation.y = std::clamp(reticleTrans_.translation.y, -15.0f, 15.0f);
}

void Player::BulletUpdate(Camera* camera)
{
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->GetIsDead(); });

	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		//’e‚ğ¶¬‚µA‰Šú‰»
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(playerTrans_.parentToTranslation, directionVector_);
		//’e‚ğ“o˜^‚·‚é
		bullets_.push_back(std::move(newBullet));
	}

	//’e‚ÌXVˆ—
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Update(camera);
	}
}

void Player::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//’e‚Ì•`‰æ
	}
}