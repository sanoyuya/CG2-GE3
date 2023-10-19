#include "DemoScene.h"
#include"Retention.h"
#include<imgui.h>
#include"PhysicsMath.h"

void DemoScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,30,-10 });
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

	ground_ = std::make_unique<Sprite>();
	groundTex_ = ground_->LoadTexture("Resources/back.png");
	ground_->Sprite3DInitialize(groundTex_);
	groundTrans_.Initialize();
	groundTrans_.translation.y = -10.0f;
	groundTrans_.rotation.x = myMath::AX_PIF / 2;
	groundTrans_.scale = { 1.0f / 5.0f,1.0f / 5.0f ,1.0f / 5.0f };

	ground2_ = std::make_unique<Sprite>();
	ground2Tex_ = ground_->LoadTexture("Resources/white1x1.png");
	ground2_->Sprite3DInitialize(ground2Tex_);
	ground2Trans_.Initialize();
	ground2Trans_.translation.y = -11.0f;
	ground2Trans_.rotation.x = myMath::AX_PIF / 2;
	ground2Trans_.scale = { 100.0f,100.0f,1.0f };

	ground3_ = std::make_unique<Sprite>();
	ground3Tex_ = ground_->LoadTexture("Resources/white1x1.png");
	ground3_->Sprite3DInitialize(ground2Tex_);
	ground3Trans_.Initialize();
	ground3Trans_.translation.y = -11.0f;
	ground3Trans_.rotation.x = myMath::AX_PIF / 2;
	ground3Trans_.scale = { 100.0f,100.0f,1.0f };

	ground4_ = std::make_unique<Sprite>();
	ground4Tex_ = ground_->LoadTexture("Resources/white1x1.png");
	ground4_->Sprite3DInitialize(ground2Tex_);
	ground4Trans_.Initialize();
	ground4Trans_.translation.y = -11.0f;
	ground4Trans_.rotation.x = myMath::AX_PIF / 2;
	ground4Trans_.scale = { 100.0f,100.0f,1.0f };
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	/*if (flame_ < 2)
	{
		num_++;
		flame_ = 0.0f;
	}*/
	flame_++;

	//正面ベクトル
	frontVec_ = pointTrans_.translation - modelTrans_.translation;
	frontVec_.normalization();

	//正面ベクトルを使ってクォータニオンを作成
	myMath::Quaternion q(baseVec_, frontVec_);
	//クォータニオンからオイラー角への変換
	//modelTrans_.rotation = { q.GetEulerAngles().x,-q.GetEulerAngles().y,0.0f };//Z軸回転はしなくて良い

	ground2Trans_.translation.z = PhysicsMath::SimpleHarmonicMotion(flame_, 100.0f,300.0f);
	ground3Trans_.translation.z = 100.0f +PhysicsMath::SimpleHarmonicMotion(flame_, 100.0f, 300.0f);
	ground4Trans_.translation.z = -100.0f +PhysicsMath::SimpleHarmonicMotion(flame_, 100.0f, 300.0f);
	

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
	groundTrans_.TransUpdate(camera_.get());
	ground2Trans_.TransUpdate(camera_.get());
	ground3Trans_.TransUpdate(camera_.get());
	ground4Trans_.TransUpdate(camera_.get());

	ImGuiUpdate();
}

void DemoScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	ground2_->DrawSprite3D(camera_.get(), ground2Trans_);
	ground3_->DrawSprite3D(camera_.get(), ground3Trans_, BillboardFlag::NonBillboard, { 0.25,0.25,0.25,1 });
	ground4_->DrawSprite3D(camera_.get(), ground4Trans_, BillboardFlag::NonBillboard, { 0.25,0.25,0.25,1 });
	ground_->DrawSprite3D(camera_.get(), groundTrans_);
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
