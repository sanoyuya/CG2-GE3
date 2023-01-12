#include "TitleScene.h"
#include"GameScene.h"
#include"PhysicsMath.h"

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
	sceneManager = SceneManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	titleBackTex = titleBack->LoadTexture("Resources/white1x1.png");
	titleBack = std::make_unique<Sprite>();
	titleBack->Sprite2DInitialize(titleBackTex);

	titleTex = title->LoadTexture("Resources/title.png");
	title= std::make_unique<Sprite>();
	title->Sprite2DInitialize(titleTex);

	pressTex = press->LoadTexture("Resources/start.png");
	press = std::make_unique<Sprite>();
	press->Sprite2DInitialize(pressTex);

	//プレイヤーのモデル
	model = std::make_unique<DrawOversight>();
	minDiceTex = Model::CreateObjModel("Resources/greenDice");
	model->SetModel(minDiceTex);
	modelPos.Initialize();
	modelPos.translation.y = -1.0;
	modelPos.scale = { 1.5f,1.5f ,1.5f };

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,7.5f,-10.0f };
	camera->SetEye(cameraPos);

	titleBGM = audioManager->LoadAudio("Resources/Sound/title.mp3");
	audioManager->ChangeVolume(titleBGM, 0.1f);
	audioManager->PlayWave(titleBGM, true);
}

void TitleScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE) || input->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
	}

	if (SceneChangeAnimation::GetInstance()->GetAnimationTimer() == 30)
	{
		audioManager->StopWave(titleBGM);
		BaseScene* scene = new GameScene();
		sceneManager->SetNextScene(scene);
	}

	if (modelPos.rotation.y > myMath::AX_PIF * 2)
	{
		modelPos.rotation.y = 0.0f;//オーバーフローしないように
	}
	modelPos.rotation.y -= 0.05f;

	camera->Update(true);
	modelPos.TransUpdate(camera.get());

	timer++;
	if (timer > 180.0f)
	{
		timer = 0.0f;
	}
}

void TitleScene::Draw()
{
	titleBack->DrawSprite2D({ 640.0f,360.0f }, { 94.0f / 255.0f,204.0f / 255.0f,104.0f / 255.0f,1.0f }, { 1280,720 });
	title->DrawSprite2D({ 640.0f,160.0f + PhysicsMath::SimpleHarmonicMotion(timer,10.0f,180.0f) }, { 121.0f / 255.0f,94.0f / 255.0f,204.0f / 255.0f,1.0f });
	press->DrawSprite2D({ 640.0f,630.0f });

	model->DrawModel(&modelPos);
}

void TitleScene::Destroy()
{
}