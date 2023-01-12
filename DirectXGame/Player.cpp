#include "Player.h"
#include"PhysicsMath.h"

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
	playerPos.Initialize();
	playerPos.translation.y = 2.0f;

	//プレイヤーの攻撃範囲の円
	attackRangeCircle = std::make_unique<Sprite>();
	attackRangeTex = attackRangeCircle->LoadTexture("Resources/circle.png");
	attackRangeCircle->Sprite3DInitialize(attackRangeTex);
	attackRangeCircleTrans.Initialize();
	attackRangeCircleTrans.rotation.x = myMath::AX_PIF / 2;
	attackRangeCircleTrans.scale = { 1.0f / 20.0f,1.0f / 20.0f ,1.0f };

	//プレイヤーの向いてる方向を指す矢印
	directionTriangle = std::make_unique<Sprite>();
	directionTex = attackRangeCircle->LoadTexture("Resources/triangle.png");
	directionTriangle->Sprite3DInitialize(directionTex);
	directionTriangleTrans.Initialize();
	directionTriangleTrans.rotation.x = myMath::AX_PI / 2;
	directionTriangleTrans.scale = { 1.0f / 15,1.0f / 15 ,1.0f };

	//体力
	hertTex = hert[0]->LoadTexture("Resources/hert.png");
	for (int i = 0; i < hert.size(); i++)
	{
		hert[i] = std::make_unique<Sprite>();
		hert[i]->Sprite2DInitialize(hertTex);
	}
	
	radius = 1.0f;
	hp = 3;
	attackPower = 1;
	angle = myMath::AX_PIF;
}

void Player::Update(Camera* camera)
{
	if (hp > 0)
	{
		if (jumpFlag == false)
		{
			Rotation();
			Move();
		}
		Movelimit();
		Attack();

		attackRangeCircleTrans.translation.x = playerPos.translation.x;
		attackRangeCircleTrans.translation.z = playerPos.translation.z;

		directionTriangleTrans.translation.x = playerPos.translation.x + sinf(angle) * directionTriangleDistance;
		directionTriangleTrans.translation.z = playerPos.translation.z + cosf(angle) * directionTriangleDistance;
		directionTriangleTrans.rotation.y = angle;

		if (damageFlag == true)
		{
			damageCoolTime++;

			if (damageCoolTime < 5 || damageCoolTime / 5 == 2 || damageCoolTime / 5 == 4 || damageCoolTime / 5 == 6 || damageCoolTime / 5 == 8 || damageCoolTime / 5 == 10 || damageCoolTime / 5 == 12 || damageCoolTime / 5 == 14)
			{
				drawFlag = false;
			}
			else if (damageCoolTime / 5 == 1 || damageCoolTime / 5 == 3 || damageCoolTime / 5 == 5 || damageCoolTime / 5 == 7 || damageCoolTime / 5 == 9 || damageCoolTime / 5 == 11 || damageCoolTime / 5 == 13 || damageCoolTime / 5 == 15)
			{
				drawFlag = true;
			}

			if (damageCoolTime > 60)
			{
				drawFlag = true;
				damageFlag = false;
				damageCoolTime = 0.0f;
			}
		}
	}
	else
	{
		deathAnimationFlag = true;
	}

	playerPos.TransUpdate(camera);

	if (deathAnimationFlag == true)
	{
		DeathAnimation(camera);
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
	if (drawFlag == true)
	{
		model->DrawModel(&playerPos);
	}

	for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
	{
		deathCube->Draw({ 1.0f ,1.0f ,1.0f ,1.0f });//背景のサイコロ
	}

	if (hp >= 1)hert[0]->DrawSprite2D({ 50 + shakeAdd,100 + shakeAdd });
	if (hp >= 2)hert[1]->DrawSprite2D({ 125 + shakeAdd,100 + shakeAdd });
	if (hp >= 3)hert[2]->DrawSprite2D({ 200 + shakeAdd,100 + shakeAdd });
}

void Player::AttackRangeDraw(Camera* camera)
{
	if (jumpFlag == false&& deathAnimationFlag==false)
	{
		directionTriangle->DrawSprite3D(camera, directionTriangleTrans);
		attackRangeCircle->DrawAnimationSpriteX3D(camera, attackRangeCircleTrans, 6, attackPower);
	}
}

void Player::Reset()
{
	playerPos.translation = { 0.0f,2.0f ,0.0f };
	directionTriangleTrans.rotation.x = myMath::AX_PIF / 2;
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

const bool& Player::GetDamageFlag()
{
	return damageFlag;
}

const bool& Player::GetDeathFlag()
{
	return deathFlag;
}

const bool& Player::GetDeathAnimationFlag()
{
	return deathAnimationFlag;
}

void Player::SetHp(const int hp)
{
	this->hp = hp;
}

void Player::SetDamageFlag(const bool damageFlag)
{
	this->damageFlag = damageFlag;
}

void Player::Attack()
{
	const float speed = 3.25f;

	if (jumpFlag == false)
	{
		attackFlag = false;
	}

	if (input->KeyboardTriggerPush(DIK_W)|| input->KeyboardTriggerPush(DIK_A) || input->KeyboardTriggerPush(DIK_S) || input->KeyboardTriggerPush(DIK_D) || input->KeyboardTriggerPush(DIK_SPACE))controllerFlag = false;
	if (input->ControllerButtonTriggerPush(A)||input->GetLeftStickVec().x != 0.0f && input->GetLeftStickVec().y != 0.0f)controllerFlag = true;

	if (jumpFlag == false && (input->KeyboardTriggerPush(DIK_SPACE) || input->ControllerButtonTriggerPush(A)))
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

	if (input->KeyboardKeepPush(DIK_W) && input->KeyboardKeepPush(DIK_A))
	{
		playerPos.translation.x += speed / 2;
		playerPos.translation.z -= speed / 2;
	}
	else if (input->KeyboardKeepPush(DIK_W) && input->KeyboardKeepPush(DIK_D))
	{
		playerPos.translation.x -= speed / 2;
		playerPos.translation.z -= speed / 2;
	}
	else if (input->KeyboardKeepPush(DIK_S) && input->KeyboardKeepPush(DIK_A))
	{
		playerPos.translation.x += speed / 2;
		playerPos.translation.z += speed / 2;
	}
	else if (input->KeyboardKeepPush(DIK_S) && input->KeyboardKeepPush(DIK_D))
	{
		playerPos.translation.x -= speed / 2;
		playerPos.translation.z += speed / 2;
	}
	else if (input->KeyboardKeepPush(DIK_W))playerPos.translation.z -= speed;
	else if (input->KeyboardKeepPush(DIK_S))playerPos.translation.z += speed;
	else if (input->KeyboardKeepPush(DIK_A))playerPos.translation.x += speed;
	else if (input->KeyboardKeepPush(DIK_D))playerPos.translation.x -= speed;

	//コントローラー
	playerPos.translation.x -= input->GetLeftStickVec().x * speed;
	playerPos.translation.z += input->GetLeftStickVec().y * speed;
}

void Player::Rotation()
{
	//キーボード
	if (controllerFlag == false)
	{
		if (input->KeyboardKeepPush(DIK_W) && input->KeyboardKeepPush(DIK_A))angle = myMath::AX_PIF * 3 / 4;
		else if (input->KeyboardKeepPush(DIK_W) && input->KeyboardKeepPush(DIK_D))angle = -myMath::AX_PIF * 3 / 4;
		else if (input->KeyboardKeepPush(DIK_S) && input->KeyboardKeepPush(DIK_A))angle = myMath::AX_PIF / 4;
		else if (input->KeyboardKeepPush(DIK_S) && input->KeyboardKeepPush(DIK_D))angle = -myMath::AX_PIF / 4;
		else if (input->KeyboardKeepPush(DIK_W))angle = myMath::AX_PIF;
		else if (input->KeyboardKeepPush(DIK_S))angle = myMath::AX_PIF * 2;
		else if (input->KeyboardKeepPush(DIK_A))angle = myMath::AX_PIF / 2;
		else if (input->KeyboardKeepPush(DIK_D))angle = -myMath::AX_PIF / 2;
	}

	//コントローラー
	else
	{
		if (input->GetLeftStickVec().x != 0.0f || input->GetLeftStickVec().y != 0.0f)
		{
			angle = -atan2(input->GetLeftStickVec().x, input->GetLeftStickVec().y);
		}
	}
	
	playerPos.rotation.y = angle;
}

void Player::DeathAnimation(Camera* camera)
{
	deathAnimationCoolTime++;
	if (deathAnimationCoolTime >= 180)
	{
		deathCubes.clear();
		deathFlag = true;
	}

	if (deathAnimationCoolTime > 80)
	{
		//爆発演出
		drawFlag = false;

		deathCubes.remove_if([](std::unique_ptr<DeathCube>& deathCube) { return deathCube->GetIsDead(); });

		if (generationFlag == false)
		{
			for (int i = 0; i < 100; i++)
			{
				//背景サイコロを生成し、初期化
				std::unique_ptr<DeathCube> newdeathCube = std::make_unique<DeathCube>();
				newdeathCube->Initialize(playerPos.translation);
				//背景サイコロを登録する
				deathCubes.push_back(std::move(newdeathCube));
			}
			generationFlag = true;
		}

		//背景サイコロの更新処理
		for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
		{
			deathCube->Update(camera, { 1.0f ,1.0f ,1.0f });
		}
	}
}