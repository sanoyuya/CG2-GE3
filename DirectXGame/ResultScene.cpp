#include "ResultScene.h"
#include"TitleScene.h"
#include "PhysicsMath.h"

void ResultScene::Initialize()
{
	input = InputManager::GetInstance();
	sceneManager = SceneManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	score = Score::GetInstance();
	score->SetTimePos({ 640,360 });

	resultBackTex = resultBack->LoadTexture("Resources/white1x1.png");
	resultBack = std::make_unique<Sprite>();
	resultBack->Sprite2DInitialize(resultBackTex);

	thanksTex = thanks->LoadTexture("Resources/thanks.png");
	thanks = std::make_unique<Sprite>();
	thanks->Sprite2DInitialize(thanksTex);

	pressTex = press->LoadTexture("Resources/start.png");
	press = std::make_unique<Sprite>();
	press->Sprite2DInitialize(pressTex);

	resultBGM = audioManager->LoadAudio("Resources/Sound/Blinded.mp3");
	audioManager->ChangeVolume(resultBGM, 0.1f);
	audioManager->PlayWave(resultBGM);
}

void ResultScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE) || input->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
	}

	if (SceneChangeAnimation::GetInstance()->GetAnimationTimer() == 30)
	{
		audioManager->StopWave(resultBGM);
		BaseScene* scene = new TitleScene();
		sceneManager->SetNextScene(scene);
	}

	timer++;
	if (timer > 180.0f)
	{
		timer = 0.0f;
	}
}

void ResultScene::Draw()
{
	resultBack->DrawSprite2D({ 640,360 }, { 121.0f / 255.0f,94.0f / 255.0f,204.0f / 255.0f,1.0f }, { 1280,720 });
	thanks->DrawSprite2D({ 640.0f,160.0f + PhysicsMath::SimpleHarmonicMotion(timer,10.0f,180.0f) }, { 94.0f / 255.0f,204.0f / 255.0f,104.0f / 255.0f,1.0f });
	press->DrawSprite2D({ 640.0f,630.0f });
	score->ScoreDraw();
}

void ResultScene::Destroy()
{
	score->Reset();
}