#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void TitleScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = { 0.0f,3.0f,-10.0f };

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	//天球
	skyDome_ = std::make_unique<Model>();
	//model->SetModelBlendMode(BlendMode::Sub);
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();

	Model::SetStaticShaderMode(ShaderMode::Phong);

	playerTex_ = skyDome_->CreateObjModel("Resources/greenDice");
	sphereTex_ = skyDome_->CreateObjModel("Resources/sphere");
	tex_ = skyDome_->CreateObjModel("Resources/purpleDice");

	bgm_ = audioManager_->LoadAudio("Resources/Sound/title.mp3",0.1f);
	audioManager_->PlayWave(bgm_);

	LevelDataInitialize();
}

void TitleScene::Destroy()
{
	audioManager_->StopWave(bgm_);
}

void TitleScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	camUpdate();

	skyDomeTrans_.TransUpdate(camera_.get());//天球

	/*time++;
	pos.y = PhysicsMath::SimpleHarmonicMotion(time,3.0f);*/

	Move();

	for (auto& object : objects_)
	{
		if (object->GetName() == "player")
		{
			object->SetPos(pos_);
		}
		if (object->GetName() == "child")
		{
			object->SetPos({ pos_.x,object->GetPos().y,pos_.z });
		}
		object->Update(camera_.get());
	}

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, { 0.0f,0.0f ,0.0f });
	lightManager_->SetPointLightColor(0, { 1.0f,1.0f,1.0f });
	lightManager_->SetPointLightAtten(0, { 0.3f,0.1f,0.1f });
}

void TitleScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	for (auto& object : objects_)
	{
		object->Draw();
	}
}

void TitleScene::camUpdate()
{
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		cameraPos_.y += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos_.y -= 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos_.x += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos_.x -= 0.05f;
	}

	camera_->SetEye(cameraPos_);
	camera_->SetTarget({ 0.0f,0.0f ,0.0f });
	camera_->Update(true);
}

void TitleScene::LevelDataInitialize()
{
	std::unique_ptr<LevelData> levelData_ = std::make_unique<LevelData>();
	levelData_.reset(LevelEditor::LoadLevelEditorFile("untitled"));

	//レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData_->objects_)
	{
		//ファイル名から登録済みモデルを検索
		std::unique_ptr<EditorObject> model = std::make_unique<EditorObject>();
		model->Initialize();

		//座標
		model->SetPos(objectData.translation);
		//回転角
		model->SetRot(objectData.rotation);
		//拡縮
		model->SetScale(objectData.scaling);
		//名前
		model->SetName(objectData.fileName);
		//コライダーの中心座標
		model->SetColliderCenter(objectData.collider.center);
		//コライダーサイズ
		model->SetColliderSize(objectData.collider.size);

		if (objectData.fileName == "player")
		{
			model->SetModel(playerTex_);
			pos_ = model->GetPos();
		}
		else if (objectData.fileName == "sphere")
		{
			model->SetModel(sphereTex_);
		}
		else
		{
			model->SetModel(tex_);
		}

		objects_.push_back(std::move(model));
	}
}

void TitleScene::Move()
{
	if (input_->KeyboardKeepPush(DIK_W))
	{
		pos_.z += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_A))
	{
		pos_.x -= 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_S))
	{
		pos_.z -= 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_D))
	{
		pos_.x += 0.05f;
	}
}
