#include "DemoScene.h"

void DemoScene::Initialize()
{
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,30,-30 });
	camera_->SetTarget({ 0,0,0 });
	camera_->Update(true);

	sprite_ = std::make_unique<Sprite>();
	spriteTex_ = sprite_->LoadTexture("Resources/reimu.png");
	sprite_->Sprite2DInitialize(spriteTex_);

	model_= std::make_unique<Model>();
	modelTex_ = Model::CreateObjModel("Resources/convenienceStore");
	model_->SetModel(modelTex_);
	modelTrans_.Initialize();
	modelTrans_.translation.z = 0.0f;
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	angle_+=0.01f;
	modelTrans_.TransUpdate(camera_.get());
}

void DemoScene::Draw()
{
	model_->DrawModel(&modelTrans_);
}
