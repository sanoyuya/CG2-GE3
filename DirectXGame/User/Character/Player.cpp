#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
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
	reticleTrans_.translation = { 0.0f,-3.0f,10.0f };
}

void Player::Update(Camera* camera)
{
	cameraTrans_.matWorld = camera->GetMatView();
	playerTrans_.parent = &cameraTrans_;
	reticleTrans_.parent = &cameraTrans_;

	playerTrans_.TransUpdate(camera);
	reticleTrans_.TransUpdate(camera);
}

void Player::Draw(Camera* camera)
{
	player_->DrawModel(&playerTrans_);
	reticle_->DrawSprite3D(camera, playerTrans_);
}

void Player::Reset()
{
}