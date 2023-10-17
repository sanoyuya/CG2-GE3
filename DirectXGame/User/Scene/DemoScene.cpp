#include "DemoScene.h"
#include"Retention.h"
#include<imgui.h>

void DemoScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,30,-30 });
	camera_->SetTarget({ 0,0,0 });
	camera_->Update(true);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome3");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();
	skyDomeTrans_.scale = { 5.0f,5.0f ,5.0f };

	sprite_ = std::make_unique<Sprite>();
	spriteTex_ = sprite_->LoadTexture("Resources/default/GodQueenProject/faleg/1_1.jpg");
	sprite_->Sprite2DInitialize(spriteTex_);

	model_= std::make_unique<Model>();
	modelTex_ = Model::CreateObjModel("Resources/F-35E");
	model_->SetModel(modelTex_);
	modelTrans_.Initialize();

	point_ = std::make_unique<Model>();
	pointTex_ = Model::CreateObjModel("Resources/sphere");
	point_->SetModel(pointTex_);
	pointTrans_.Initialize();
	pointTrans_.translation = { 0,0,10 };
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	if (flame_ < 2)
	{
		num_++;
		flame_ = 0.0f;
	}

	//正面ベクトル
	frontVec_ = pointTrans_.translation - modelTrans_.translation;
	frontVec_.normalization();

	//正面ベクトルを使ってクォータニオンを作成
	myMath::Quaternion q(baseVec_, frontVec_);
	//クォータニオンからオイラー角への変換
	//modelTrans_.rotation = { q.GetEulerAngles().x,-q.GetEulerAngles().y,0.0f };//Z軸回転はしなくて良い
	

	if (input_->KeyboardKeepPush(DIK_W))
	{
		pointTrans_.translation.z += 0.1f;
	}
	if (input_->KeyboardKeepPush(DIK_S))
	{
		pointTrans_.translation.z -= 0.1f;
	}
	if (input_->KeyboardKeepPush(DIK_A))
	{
		pointTrans_.translation.x -= 0.1f;
	}
	if (input_->KeyboardKeepPush(DIK_D))
	{
		pointTrans_.translation.x += 0.1f;
	}
	if (input_->KeyboardKeepPush(DIK_Q))
	{
		pointTrans_.translation.y += 0.1f;
	}
	if (input_->KeyboardKeepPush(DIK_E))
	{
		pointTrans_.translation.y -= 0.1f;
	}
	
	skyDomeTrans_.TransUpdate(camera_.get());
	pointTrans_.TransUpdate(camera_.get());
	modelTrans_.TransUpdate(camera_.get(),&q);

	ImGuiUpdate();
}

void DemoScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	model_->DrawModel(&modelTrans_);
	point_->DrawModel(&pointTrans_);
	//sprite_->DrawAnimationSpriteY2D(Retention::GetInstance()->GetWindowsCenter(), 16, num_, {1,1,1,1}, {1,1}, -myMath::AX_PIF / 2);
}

void DemoScene::ImGuiUpdate()
{
	ImGui::Begin("Point");
	ImGui::SliderFloat3("pointPos", &pointTrans_.translation.x, -20, 20);
	ImGui::End();

	ImGui::Begin("Model");
	ImGui::SliderFloat3("modelPos", &modelTrans_.translation.x, -20, 20);
	ImGui::Text("modelRot:%f,%f,%f", modelTrans_.rotation.x, modelTrans_.rotation.y, modelTrans_.rotation.z);
	ImGui::End();
}
