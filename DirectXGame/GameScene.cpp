#include "GameScene.h"
#include"PhysicsMath.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = audioManager->GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,length,0.000001f };

	player = std::make_unique<Player>();
	player->Initialize();

	enemyTex = Model::CreateObjModel("Resources/cube");
	Enemy::LoadTexture(enemyTex);

	//�V��
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//�X�e�[�W�L���[�u
	cube = std::make_unique<DrawOversight>();
	cubeTex = Model::CreateObjModel("Resources/cube");
	cube->SetModel(cubeTex);
	cubeTrans.scale = { 25.0f,1.0f ,25.0f };
	cubeTrans.Initialize();
}

void GameScene::Update()
{
	EnemyDead();
	EnemyUpdate();

	CamMove();
	modelTrans.TransUpdate(camera.get());//�V��
	cubeTrans.TransUpdate(camera.get());//�X�e�[�W�L���[�u
	player->Update(camera.get());
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);
	cube->DrawModel(&cubeTrans);
	EnemyDraw();
	player->Draw();
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

void GameScene::EnemyDead()
{
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy_) { return enemy_->GetIsDead(); });
}

void GameScene::EnemyUpdate()
{
	//�G�̐�������
	coolTime++;
	if (coolTime > 10)
	{
		myMath::Vector3 position = { 0.0f,2.0f,0.0f };
		//Enemy�𐶐����A������
		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize(position);
		//Enemy��o�^����
		enemys.push_back(std::move(newEnemy));

		coolTime = 0.0f;
	}

	//�G�̍X�V����
	for (const std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update(camera.get());
	}
}

void GameScene::EnemyDraw()
{
	for (const std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw();//�v���C���[�Ɍ������Ă���G
	}
}

void GameScene::Reset()
{
	cameraPos = { 0.0f,length,0.0f };
}