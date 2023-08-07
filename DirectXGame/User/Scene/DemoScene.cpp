#include "DemoScene.h"

void DemoScene::Initialize()
{
	sprite_ = std::make_unique<Sprite>();
	spriteTex_ = sprite_->LoadTexture("Resources/reimu.png");
	sprite_->Sprite2DInitialize(spriteTex_);
}

void DemoScene::Destroy()
{

}

void DemoScene::Update()
{
	angle_+=0.01f;
}

void DemoScene::Draw()
{
	sprite_->DrawCircleGaugeSprite2D({ 640.0f,540.0f }, angle_);
}
