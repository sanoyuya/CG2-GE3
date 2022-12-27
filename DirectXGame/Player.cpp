#include "Player.h"

uint32_t Player::minDiceTex;
uint32_t Player::maxDiceTex;
uint32_t Player::directionTex;

Player::Player()
{
}

Player::~Player()
{
}

const void Player::LoadTexture(PlayerTexData& texture)
{
	minDiceTex = texture.minDice;
	maxDiceTex = texture.maxDice;
	directionTex = texture.direction;
}

void Player::Initialize()
{
	input = InputManager::GetInstance();

	model = std::make_unique<DrawOversight>();
	minDiceTex = Model::CreateObjModel("Resources/greenDice");
	maxDiceTex = Model::CreateObjModel("Resources/purpleDice");
	model->SetModel(minDiceTex);
	playerPos.translation.y = 2.0f;
	playerPos.Initialize();
	radius = 1.0f;
	hp = 3;
}

void Player::Update(Camera* camera)
{
	Move();
	Movelimit();
	Attack();
	playerPos.TransUpdate(camera);
}

void Player::Movelimit()
{
	if (playerPos.translation.x <= -23.0f)
	{
		playerPos.translation.x = -23.0f;
	}
	else if (playerPos.translation.x >= 23.0f)
	{
		playerPos.translation.x = 23.0f;
	}
	if (playerPos.translation.z <= -23.0f)
	{
		playerPos.translation.z = -23.0f;
	}
	else if (playerPos.translation.z >= 23.0f)
	{
		playerPos.translation.z = 23.0f;
	}
}

void Player::Draw()
{
	model->DrawModel(&playerPos);
}

const Transform& Player::GetTransform()
{
	return playerPos;
}

const float& Player::GetRadius()
{
	return radius;
}

const uint8_t& Player::GetHp()
{
	return hp;
}

const bool& Player::GetJumpFlag()
{
	return jumpFlag;
}

void Player::SetHp(const uint8_t hp)
{
	this->hp = hp;
}

void Player::Attack()
{
	if (jumpFlag == false && input->KeyboardTriggerPush(DIK_SPACE))
	{
		jumpFlag = true;
		gravity = 3.0f;
	}

	if (jumpFlag == true)
	{
		gravity -= 0.25f;
		playerPos.rotation.x += static_cast<float>(myMath::GetRand(-0.5f, 0.5f));
		playerPos.rotation.y += static_cast<float>(myMath::GetRand(-0.5f, 0.5f));
		playerPos.rotation.z += static_cast<float>(myMath::GetRand(-0.5f, 0.5f));
	}
	playerPos.translation.y += gravity;
	if (jumpFlag == true && playerPos.translation.y <= 1.0f)
	{
		//着地
		
		//ここでダメージ判定
		//攻撃範囲*サイコロの目で判定を取る
		playerPos.translation.y = 2.0f;
		gravity = 0.0f;

		attackPower = static_cast<uint8_t>(myMath::GetRand(1, 6));

		switch (attackPower)
		{
		case 1:

			model->SetModel(minDiceTex);
			playerPos.rotation = { 0.0f,0.0f ,0.0f };//0の目

			break;

		case 2:

			model->SetModel(minDiceTex);
			playerPos.rotation = { -myMath::AX_PIF / 2,0.0f ,0.0f };//2の目

			break;

		case 3:

			model->SetModel(minDiceTex);
			playerPos.rotation = { 0.0f,0.0f ,myMath::AX_PIF / 2 };//3の目

			break;

		case 4:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { 0.0f,0.0f ,-myMath::AX_PIF / 2 };//4の目

			break;

		case 5:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { myMath::AX_PIF,0.0f ,0.0f };//5の目

			break;

		case 6:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { myMath::AX_PIF,0.0f ,0.0f };//6の目

			break;
		}
		jumpFlag = false;
	}
}

void Player::Move()
{
	if (input->KeyboardKeepPush(DIK_W))
	{
		playerPos.translation.z -= 0.25f;
	}
	if (input->KeyboardKeepPush(DIK_S))
	{
		playerPos.translation.z += 0.25f;
	}
	if (input->KeyboardKeepPush(DIK_A))
	{
		playerPos.translation.x += 0.25f;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		playerPos.translation.x -= 0.25f;
	}
}