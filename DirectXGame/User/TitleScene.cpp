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

	//�V��
	skyDome = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	skyDomeTex = Model::CreateObjModel("Resources/skydome2");
	skyDome->SetModel(skyDomeTex);
	skyDomeTrans.Initialize();

	playerTex = skyDome->CreateObjModel("Resources/greenDice");
	sphereTex = skyDome->CreateObjModel("Resources/sphere");
	tex = skyDome->CreateObjModel("Resources/purpleDice");

	levelData = std::make_unique<LevelData>();
	levelData.reset(LevelEditor::LoadLevelEditorFile("untitled"));

	//���x���f�[�^����I�u�W�F�N�g�𐶐��A�z�u
	for (auto& objectData : levelData->objects_)
	{
		//�t�@�C��������o�^�ς݃��f��������
		EditorObject* model = new EditorObject;
		model->Initialize();
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end())
		{
			model = it->second;
		}

		//���W
		model->SetPos(objectData.translation);
		//��]�p
		model->SetRot(objectData.rotation);
		//�g�k
		model->SetScale(objectData.scaling);
		//���O
		model->SetName(objectData.fileName);
		//�R���C�_�[�̒��S���W
		model->SetColliderCenter(objectData.collider.center);
		//�R���C�_�[�T�C�Y
		model->SetColliderSize(objectData.collider.size);

		if (objectData.fileName == "player")
		{
			model->SetModel(playerTex);
			pos = model->GetPos();
		}
		else if (objectData.fileName == "sphere")
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

	skyDomeTrans.TransUpdate(camera.get());//�V��

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
