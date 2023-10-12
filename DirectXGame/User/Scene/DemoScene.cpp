#include "DemoScene.h"

void DemoScene::Initialize()
{
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,30,-30 });
	camera_->SetTarget({ 0,0,0 });
	camera_->Update(true);

	sprite_ = std::make_unique<Sprite>();
	spriteTex_ = sprite_->LoadTexture("Resources/default/GodQueenProject/faleg/1_1.jpg");
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
	if (flame_ < 2)
	{
		num_++;
		flame_ = 0.0f;
	}
	angle_+=0.01f;
	modelTrans_.TransUpdate(camera_.get());
}

void DemoScene::Draw()
{
	model_->DrawModel(&modelTrans_);
	sprite_->DrawAnimationSpriteY2D(windowsCenter_, 16, num_,{1,1,1,1},{1,1},-myMath::AX_PIF/2);
}
