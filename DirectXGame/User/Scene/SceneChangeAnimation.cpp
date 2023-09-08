#include "SceneChangeAnimation.h"
#include"SceneManager.h"
#include"EasingFunction.h"

void SceneChangeAnimation::StaticInitialize()
{
	back_ = std::make_unique<Sprite>();
	backTex_ = back_->LoadTexture("Resources/white1x1.png");
	back_->Sprite2DInitialize(backTex_);
}

void SceneChangeAnimation::Update()
{
	if (animationFlag_ == true)
	{
		animationTimer_++;
	}

	if (animationTimer_ <= 90.0f)
	{
		alpha_ = static_cast<float>(Easing::EaseInQuint(static_cast<double>(animationTimer_), 0.0f, 1.0f, 90.0f));
	}
	else if (animationTimer_ == 91.0f)
	{
		SceneManager::GetInstance()->ChangeScene(sceneName_);
	}
	else
	{
		alpha_ = static_cast<float>(Easing::EaseInOutQuint(static_cast<double>(animationTimer_ - 90.0f), 1.0f, 0.0f, 90.0f));
	}

	if (animationTimer_ >= maxAnimationTime)
	{
		Reset();
	}
}

void SceneChangeAnimation::Change(const std::string& sceneName)
{
	animationFlag_ = true;
	sceneName_ = sceneName;
}

void SceneChangeAnimation::Draw()
{
	back_->DrawSprite2D({ 640.0f,360.0f }, { 0.0f,0.0f,0.0f ,alpha_ }, { 1280.0f,720.0f });
}

void SceneChangeAnimation::SetAnimationFlag(bool flag)
{
	animationFlag_ = flag;
}

SceneChangeAnimation* SceneChangeAnimation::GetInstance()
{
	static SceneChangeAnimation instance;
	return &instance;
}

void SceneChangeAnimation::Reset()
{
	animationTimer_ = 0;
	alpha_ = 0.0f;
	animationFlag_ = false;
}