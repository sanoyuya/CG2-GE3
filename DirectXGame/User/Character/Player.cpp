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
}

void Player::Update(Camera* camera)
{
	cameraTrans_.matWorld = camera->GetMatView();
	playerTrans_.parent = &cameraTrans_;

	playerTrans_.TransUpdate(camera);
}

void Player::Draw()
{
	player_->DrawModel(&playerTrans_);
}

void Player::Reset()
{
}