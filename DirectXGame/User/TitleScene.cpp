#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,3.0f,-10.0f };

	//天球
	skyDome = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	skyDomeTex = Model::CreateObjModel("Resources/skydome2");
	skyDome->SetModel(skyDomeTex);
	skyDomeTrans.Initialize();

	playerTex = skyDome->CreateObjModel("Resources/greenDice");
	sphereTex = skyDome->CreateObjModel("Resources/sphere");
	tex = skyDome->CreateObjModel("Resources/purpleDice");

	levelData = LevelEditor::LoadLevelEditorFile("untitled");

	//レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData->objects_)
	{
		//ファイル名から登録済みモデルを検索
		EditorObject* model = new EditorObject;
		model->Initialize();
		decltype(models)::iterator it = models.find(objectData.fileName_);
		if (it != models.end())
		{
			model = it->second;
		}

		//座標
		model->SetPos(objectData.translation_);
		//回転角
		model->SetRot(objectData.rotation_);
		//拡縮
		model->SetScale(objectData.scaling_);
		//名前
		model->SetName(objectData.fileName_);
		//コライダーの中心座標
		model->SetColliderCenter(objectData.collider_.center_);
		//コライダーサイズ
		model->SetColliderSize(objectData.collider_.size_);

		if (objectData.fileName_ == "player")
		{
			model->SetModel(playerTex);
			pos = model->GetPos();
		}
		else if (objectData.fileName_ == "sphere")
		{
			model->SetModel(sphereTex);
		}
		else
		{
			model->SetModel(tex);
		}

		objects.push_back(model);
	}
}

void TitleScene::Destroy()
{
	
}

void TitleScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	camUpdate();

	skyDomeTrans.TransUpdate(camera.get());//天球

	/*time++;
	pos.y = PhysicsMath::SimpleHarmonicMotion(time,3.0f);*/

	Move();

	for (auto& object : objects)
	{
		if (object->GetName() == "player")
		{
			object->SetPos(pos);
		}
		if (object->GetName() == "child")
		{
			object->SetPos({ pos.x,object->GetPos().y,pos.z });
		}
		object->Update(camera.get());
	}
}

void TitleScene::Draw()
{
	skyDome->DrawModel(&skyDomeTrans);
	for (auto& object : objects)
	{
		object->Draw();
	}
}

void TitleScene::camUpdate()
{
	if (input->KeyboardKeepPush(DIK_UP))
	{
		cameraPos.y += 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos.y -= 0.05f;
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

void TitleScene::Move()
{
	if (input->KeyboardKeepPush(DIK_W))
	{
		pos.z += 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_A))
	{
		pos.x -= 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_S))
	{
		pos.z -= 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		pos.x += 0.05f;
	}
}
