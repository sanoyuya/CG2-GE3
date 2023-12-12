#include "GroundBack.h"
#include"PhysicsMath.h"
uint32_t GroundBack::groundBackTex_;

void GroundBack::Initialize(myMath::Vector2 translation,myMath::Vector2 size)
{
	groundBack_ = std::make_unique<Model>();
	groundBack_->SetModel(groundBackTex_);
	groundBackTrans_.Initialize();
	groundBackTrans_.translation = { translation.x,-0.1f,translation.y };
	groundBackTrans_.scale = { size.x,1.0f,size.y };
}

void GroundBack::Update(Camera* camera, GameTimer* gameTimer)
{
	alpha_ = PhysicsMath::SimpleHarmonicMotion(gameTimer->GetFlameCount(), 0.5f, 360.0f) + 0.75f;
	groundBackTrans_.TransUpdate(camera);
}

void GroundBack::Draw()
{
	groundBack_->DrawModel(&groundBackTrans_, { 78.0f / 255.0f,175.0f / 255.0f,254.0f / 255.0f,alpha_ });
}

void GroundBack::LoadAsset()
{
	groundBackTex_ = Model::CreateObjModel("Resources/groundBack");
}