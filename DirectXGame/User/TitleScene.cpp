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
	tex= skyDome->CreateObjModel("Resources/purpleDice");

	levelData = LevelEditor::LoadLevelEditorFile("untitled");

	//レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData->objects)
	{
		//ファイル名から登録済みモデルを検索
		Model* model = model = new Model;
		Transform transform;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end())
		{
			model = it->second;
		}

		if (objectData.fileName == "player")
		{
			model->SetModel(playerTex);
		}
		else if (objectData.fileName == "sphere")
		{
			model->SetModel(sphereTex);
		}
		else
		{
			model->SetModel(tex);
		}
		transform.Initialize();

		//座標
		transform.translation = objectData.translation;
		//回転角
		transform.rotation = objectData.rotation;
		//拡縮
		transform.scale = objectData.scaling;

		objects.push_back(model);
		transforms.push_back(transform);
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

	for (auto& object : objects)
	{
		for (auto& transform : transforms)
		{
			transform.TransUpdate(camera.get());
		}
	}
}

void TitleScene::Draw()
{
	skyDome->DrawModel(&skyDomeTrans);
	for (auto& object : objects)
	{
		for (auto& transform : transforms)
		{
			object->DrawModel(&transform);
		}
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