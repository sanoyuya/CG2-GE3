#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
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
}

void Player::Update(Camera* camera)
{
	Move();
	Attack();
	playerPos.TransUpdate(camera);
}

void Player::Draw()
{
	model->DrawModel(&playerPos);
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
		playerPos.rotation.x += myMath::GetRand(-0.5f, 0.5f);
		playerPos.rotation.y += myMath::GetRand(-0.5f, 0.5f);
		playerPos.rotation.z += myMath::GetRand(-0.5f, 0.5f);
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
			playerPos.rotation = { -myMath::AX_PI / 2,0.0f ,0.0f };//2の目

			break;

		case 3:

			model->SetModel(minDiceTex);
			playerPos.rotation = { 0.0f,0.0f ,myMath::AX_PI / 2 };//3の目

			break;

		case 4:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { 0.0f,0.0f ,-myMath::AX_PI / 2 };//4の目

			break;

		case 5:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { myMath::AX_PI,0.0f ,0.0f };//5の目

			break;

		case 6:

			model->SetModel(maxDiceTex);
			playerPos.rotation = { myMath::AX_PI,0.0f ,0.0f };//6の目

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