#include "GameScene.h"
#include"PhysicsMath.h"

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = audioManager->GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,length,0.000001f };

	player = std::make_unique<Player>();
	player->Initialize();

	enemyTex = TextureManager::GetInstance()->LoadTexture("Resources/enemy.png");
	Enemy::LoadTexture(enemyTex);//敵のテクスチャデータ読み込み

	//天球
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//背景
	backSprite = std::make_unique<Sprite>();
	backSpriteTex = backSprite->LoadTexture("Resources/white1x1.png");
	backSprite->Sprite3DInitialize(backSpriteTex);
	backSpriteTrans.Initialize();
	backSpriteTrans.translation = { 0.0f,0.0f ,0.0f };
	backSpriteTrans.scale = { 90.0f,50.0f,0.0f };
	backSpriteTrans.rotation = { myMath::AX_PIF / 2,0.0f,0.0f };

	backLeftSprite = std::make_unique<Sprite>();
	backLeftSprite->Sprite3DInitialize(backSpriteTex);
	backLeftSpriteTrans.Initialize();
	backLeftSpriteTrans.translation = { 35.0f,0.0f ,0.0f };
	backLeftSpriteTrans.scale = { 20.0f,50.0f,0.0f };
	backLeftSpriteTrans.rotation = { myMath::AX_PIF / 2,0.0f,0.0f };

	backRightSprite = std::make_unique<Sprite>();
	backRightSprite->Sprite3DInitialize(backSpriteTex);
	backRightSpriteTrans.Initialize();
	backRightSpriteTrans.translation = { -35.0f,0.0f ,0.0f };
	backRightSpriteTrans.scale = { 20.0f,50.0f,0.0f };
	backRightSpriteTrans.rotation = { myMath::AX_PIF / 2,0.0f,0.0f };

	backDiceTex = TextureManager::GetInstance()->LoadTexture("Resources/backDice.png");
	BackDice::LoadTexture(backDiceTex);

	shadowSprite = std::make_unique<Sprite>();
	shadowSpriteTex = shadowSprite->LoadTexture("Resources/shadow.png");
	shadowSprite->Sprite3DInitialize(shadowSpriteTex);
	shadowSpriteTrans.Initialize();
	shadowSpriteTrans.translation = { 0.0f,0.0f ,0.0f };
	shadowSpriteTrans.scale = { 50.0f,50.0f ,0.0f };
	shadowSpriteTrans.rotation = { myMath::AX_PIF / 2,0.0f,0.0f };
}

void GameScene::Destroy()
{
}

void GameScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_R))
	{
		Reset();
		player->Reset();
	}
	EnemyDead();
	BackDiceDead();

	BackDiceUpdate();
	CamMove();
	modelTrans.TransUpdate(camera.get());//天球

	backSpriteTrans.translation = { player->GetShakeAdd(),player->GetShakeAdd() ,0.0f };
	backSpriteTrans.Update();
	shadowSpriteTrans.translation = { player->GetShakeAdd(),player->GetShakeAdd() ,0.0f };
	shadowSpriteTrans.Update();
	backLeftSpriteTrans.translation = { 35.0f + player->GetShakeAdd(),player->GetShakeAdd() ,0.0f };
	backLeftSpriteTrans.Update();
	backRightSpriteTrans.translation = { -35.0f + player->GetShakeAdd(),player->GetShakeAdd() ,0.0f };
	backRightSpriteTrans.Update();

	player->Update(camera.get());
	EnemyUpdate();
}

void GameScene::Draw()
{
	colorTime++;
	colorR = 0.25f + PhysicsMath::SimpleHarmonicMotion(colorTime, 0.025f, 1200.0f);
	colorG = 0.15f + PhysicsMath::SimpleHarmonicMotion(colorTime, 0.025f, 800.0f);
	colorB = 0.25f + PhysicsMath::SimpleHarmonicMotion(colorTime, 0.025f, 400.0f);
	backSprite->DrawSprite3D(camera.get(), backSpriteTrans, BillboardFlag::NonBillboard, { colorR,colorG,colorB,1.0f });

	shadowSprite->DrawSprite3D(camera.get(), shadowSpriteTrans);
	shadowSprite->DrawSprite3D(camera.get(), shadowSpriteTrans);

	BackDiceDraw();

	player->AttackRangeDraw(camera.get());

	backLeftSprite->DrawSprite3D(camera.get(), backLeftSpriteTrans, BillboardFlag::NonBillboard, { colorR,colorG,colorB,1.0f });
	backRightSprite->DrawSprite3D(camera.get(), backRightSpriteTrans, BillboardFlag::NonBillboard, { colorR,colorG,colorB,1.0f });

	model->DrawModel(&modelTrans);
	EnemyDraw();
	player->Draw(camera.get());
}

void GameScene::Rotation()
{
	if (input->KeyboardKeepPush(DIK_A))
	{

	}
	if (input->KeyboardKeepPush(DIK_D))
	{

	}
}

void GameScene::CamMove()
{
	if (input->KeyboardKeepPush(DIK_UP))
	{
		cameraPos.y += 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos.y -= 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos.x += 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos.x -= 0.05f;
	}

	camera->SetEye(cameraPos);
	camera->SetTarget({ 0.0f,0.0f ,0.0f });
	camera->Update(true);
}

void GameScene::BackDiceDead()
{
	backDices.remove_if([](std::unique_ptr<BackDice>& backDice) { return backDice->GetIsDead(); });
}

void GameScene::BackDiceUpdate()
{
	//背景サイコロの生成処理
	backDiceCoolTime++;
	if (backDiceCoolTime > 75)
	{
		myMath::Vector3 position = { static_cast<float>(myMath::GetRand(-20.0f,20.0f)),0.0f,static_cast<float>(myMath::GetRand(25.0f,30.0f)) };
		uint16_t num = static_cast<uint16_t>(myMath::GetRand(1, 6));

		//背景サイコロを生成し、初期化
		std::unique_ptr<BackDice> newBackDice = std::make_unique<BackDice>();
		newBackDice->Initialize(position, num);
		//背景サイコロを登録する
		backDices.push_back(std::move(newBackDice));

		backDiceCoolTime = 0.0f;
	}

	//背景サイコロの更新処理
	for (const std::unique_ptr<BackDice>& backDice : backDices)
	{
		backDice->Update(camera.get());
	}
}

void GameScene::BackDiceDraw()
{
	for (const std::unique_ptr<BackDice>& backDice : backDices)
	{
		backDice->Draw(camera.get(), { colorR ,colorG ,colorB ,1.0f });//背景のサイコロ
	}
}

void GameScene::EnemyDead()
{
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy_) { return enemy_->GetIsDead(); });
}

void GameScene::EnemyUpdate()
{
	//敵の生成処理
	coolTime++;
	if (coolTime > 50)
	{
		myMath::Vector3 position = { static_cast<float>(myMath::GetRand(-23.0f,23.0f)),0.0f,static_cast<float>(myMath::GetRand(-23.0f,23.0f)) };
		//Enemyを生成し、初期化
		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize(position);
		//Enemyを登録する
		enemys.push_back(std::move(newEnemy));

		coolTime = 0.0f;
	}

	//敵の更新処理
	for (const std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update(camera.get(), player.get());
	}
}

void GameScene::EnemyDraw()
{
	for (const std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw(camera.get());//プレイヤーに向かってくる敵
	}
}

void GameScene::Reset()
{
	cameraPos = { 0.0f,length,0.000001f };
	backDices.clear();
	enemys.clear();
}