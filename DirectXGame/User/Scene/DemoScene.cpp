#include "DemoScene.h"
#include<imgui.h>
#include"PhysicsMath.h"

void DemoScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,30,-30 });
	camera_->SetTarget({ 0,30,0 });
	camera_->Update(true);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();
	skyDomeTrans_.scale = { 5.0f,5.0f ,5.0f };

	sprite_ = std::make_unique<Sprite3D>();
	spriteTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/attention.png");
	sprite_->Sprite3DInitialize(spriteTex_);
	spriteTrans_.Initialize();
	spriteTrans_.scale = { 0.1f,0.1f ,1.0f };
	spriteTrans_.translation = { -10.0f,30.0f,0.0f };

	ddsSprite_ = std::make_unique<Sprite3D>();
	ddsSpriteTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/attention.dds");
	ddsSprite_->Sprite3DInitialize(ddsSpriteTex_);
	ddsSpriteTrans_.Initialize();
	ddsSpriteTrans_.scale = { 0.1f,0.1f ,1.0f };
	ddsSpriteTrans_.translation= { 10.0f,30.0f,0.0f };
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	spriteTrans_.TransUpdate(camera_.get());
	ddsSpriteTrans_.TransUpdate(camera_.get());
	skyDomeTrans_.TransUpdate(camera_.get());

	ImGuiUpdate();
}

void DemoScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	sprite_->DrawSprite3D(camera_.get(), spriteTrans_);
	ddsSprite_->DrawSprite3D(camera_.get(), ddsSpriteTrans_);
}

void DemoScene::ImGuiUpdate()
{
	
}
