#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(const PlayerData& playerData)
{
	Load(playerData);
	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
}

void Player::Update(Camera* camera)
{
	playerTrans_.TransUpdate(camera);
}

void Player::Draw()
{
	player_->DrawModel(&playerTrans_);
}

void Player::ReLoad(const PlayerData& playerData)
{
	Reset();
	Load(playerData);
}

void Player::Load(const PlayerData& playerData)
{
	playerTrans_.translation = playerData.pos;
	playerTrans_.rotation = playerData.rotation;
	playerTrans_.scale = playerData.scale;
}

void Player::Reset()
{
}