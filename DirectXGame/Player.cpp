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

	//プレイヤーのモデル
	model = std::make_unique<DrawOversight>();
	minDiceTex = Model::CreateObjModel("Resources/greenDice");
	maxDiceTex = Model::CreateObjModel("Resources/purpleDice");
	model->SetModel(minDiceTex);
	playerPos.translation.y = 2.0f;
	playerPos.Initialize();

	//プレイヤーの攻撃範囲の円
	attackRangeCircle = std::make_unique<Sprite>();
	attackRangeTex = attackRangeCircle->LoadTexture("Resources/circle.png");
	attackRangeCircle->Sprite3DInitialize(attackRangeTex);
	attackRangeCircleTrans.Initialize();
	attackRangeCircleTrans.rotation.x = myMath::AX_PI / 2;
	attackRangeCircleTrans.scale = { 1.0f / 20.0f,1.0f / 20.0f ,1.0f };

	//プレイヤーの向いてる方向を指す矢印
	directionTriangle = std::make_unique<Sprite>();
	directionTex = attackRangeCircle->LoadTexture("Resources/triangle.png");
	directionTriangle->Sprite3DInitialize(directionTex);
	directionTriangleTrans.Initialize();
	directionTriangleTrans.rotation.x = myMath::AX_PI / 2;
	directionTriangleTrans.scale = { 1.0f/15,1.0f / 15 ,1.0f };

	//体力
	hertTex = hert[0]->LoadTexture("Resources/hert.png");
	for (int i = 0; i < hert.size(); i++)
	{
		hert[i] = std::make_unique<Sprite>();
		hert[i]->Sprite3DInitialize(hertTex);
		hertTrans[i].Initialize();
		hertTrans[i].translation.z = -15.0f;
		hertTrans[i].rotation.x = myMath::AX_PI / 2;
		hertTrans[i].rotation.y = myMath::AX_PI;
		hertTrans[i].scale = { 1.0f / 15,1.0f / 15 ,1.0f };
	}
	hertTrans[0].translation.x = 40.0f;
	hertTrans[1].translation.x = 35.0f;
	hertTrans[2].translation.x = 30.0f;

	radius = 1.0f;
	hp = 3;
	attackPower = 1;
	angle = myMath::AX_PIF;
}

void Player::Update(Camera* camera)
{
	if (jumpFlag == false)
	{
		Rotation();
		Move();
	}
	Movelimit();
	Attack();
	if (hp <= 0)hp = 0;
	playerPos.TransUpdate(camera);

	attackRangeCircleTrans.translation.x = playerPos.translation.x;
	attackRangeCircleTrans.translation.z = playerPos.translation.z;
	attackRangeCircleTrans.TransUpdate(camera);

	directionTriangleTrans.translation.x = playerPos.translation.x + sinf(angle) * directionTriangleDistance;
	directionTriangleTrans.translation.z = playerPos.translation.z + cosf(angle) * directionTriangleDistance;
	directionTriangleTrans.rotation.y = angle;
	directionTriangleTrans.TransUpdate(camera);

	hertTrans[0].translation.x = 40.0f + shakeAdd;
	hertTrans[1].translation.x = 35.0f + shakeAdd;
	hertTrans[2].translation.x = 30.0f + shakeAdd;
	for (int i = 0; i < hert.size(); i++)
	{
		hertTrans[i].translation.z = -15.0f + shakeAdd;
	}
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

void Player::Draw(Camera* camera)
{
	model->DrawModel(&playerPos);

	if (hp >= 1)hert[0]->DrawSprite3D(camera, hertTrans[0]);
	if (hp >= 2)hert[1]->DrawSprite3D(camera, hertTrans[1]);
	if (hp >= 3)hert[2]->DrawSprite3D(camera, hertTrans[2]);
}

void Player::AttackRangeDraw(Camera* camera)
{
	if (jumpFlag == false)
	{
		directionTriangle->DrawSprite3D(camera, directionTriangleTrans);
		attackRangeCircle->DrawAnimationSpriteX3D(camera, attackRangeCircleTrans,6, attackPower);
	}
}

void Player::Reset()
{
	playerPos.translation = { 0.0f,2.0f ,0.0f };
	directionTriangleTrans.rotation.x = myMath::AX_PI / 2;
	radius = 1.0f;
	hp = 3;
	attackPower = 1;
	angle = myMath::AX_PIF;
}

const Transform& Player::GetTransform()
{
	return playerPos;
}

const float& Player::GetRadius()
{
	return radius;
}

const int& Player::GetHp()
{
	return hp;
}

const bool& Player::GetJumpFlag()
{
	return jumpFlag;
}

const float& Player::GetShakeAdd()
{
	return shakeAdd;
}

const bool& Player::GetAttackFlag()
{
	return attackFlag;
}

void Player::SetHp(const int hp)
{
	this->hp = hp;
}

void Player::Attack()
{
	const float speed = 3.25f;

	if (jumpFlag == false)
	{
		attackFlag = false;
	}

	if (jumpFlag == false && (input->KeyboardTriggerPush(DIK_SPACE)||input->ControllerButtonTriggerPush(A)))
	{
		jumpFlag = true;
		gravity = 2.0f;
	}

	if (jumpFlag == true)
	{
		gravity -= 0.1f;

		//強制移動
		playerPos.translation.x += sinf(angle) * speed / 40 * attackPower;
		playerPos.translation.z += cosf(angle) * speed / 40 * attackPower;

		//回転
		playerPos.rotation.x += 0.25f;
	}

	playerPos.translation.y += gravity;
	if (jumpFlag == true && playerPos.translation.y <= 1.0f)
	{
		//着地
		
		//ここでダメージ判定
		attackFlag = true;

		//攻撃範囲*サイコロの目で判定を取る
		playerPos.translation.y = 2.0f;

		attackPower = static_cast<uint16_t>(myMath::GetRand(1, 6));

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

		shakeFlag = true;
		gravity = 0.0f;
		jumpFlag = false;
	}

	//画面が揺れる演出
	if (shakeFlag == true)
	{
		shakeTimer++;
		shakeAdd = myMath::GetRand(-shakePower, shakePower);
		if (shakeTimer >= 10)
		{
			shakeTimer = 0.0f;
			shakeFlag = false;
		}
	}
	else
	{
		shakeAdd = 0.0f;
	}
}

void Player::Move()
{
	const float speed = 0.25f;

	//キーボード
	if (input->KeyboardKeepPush(DIK_W))
	{
		playerPos.translation.z -= speed;
	}
	if (input->KeyboardKeepPush(DIK_S))
	{
		playerPos.translation.z += speed;
	}
	if (input->KeyboardKeepPush(DIK_A))
	{
		playerPos.translation.x += speed;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		playerPos.translation.x -= speed;
	}

	//コントローラー
	playerPos.translation.x -= input->GetLeftStickVec().x * speed;
	playerPos.translation.z += input->GetLeftStickVec().y * speed;
}

void Player::Rotation()
{
	//コントローラー
	if (input->GetLeftStickVec().x != 0.0f || input->GetLeftStickVec().y != 0.0f)
	{
		angle = -atan2(input->GetLeftStickVec().x, input->GetLeftStickVec().y);
	}
	playerPos.rotation.y = angle;
}