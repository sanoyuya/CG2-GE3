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
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	skyDomeTrans_.TransUpdate(camera_.get());

	ImGuiUpdate();
}

void DemoScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
}

void DemoScene::ImGuiUpdate()
{
	
}
