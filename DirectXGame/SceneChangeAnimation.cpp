#include "SceneChangeAnimation.h"

void SceneChangeAnimation::Initialize()
{
	animationSprite = std::make_unique<Sprite>();
	animationTex = animationSprite->LoadTexture("Resources/white1x1.png");
	animationSprite->Sprite2DInitialize(animationTex);
}

void SceneChangeAnimation::Update()
{
	if (animationFlag == true)
	{
		animationTimer++;
		if (animationTimer <= 30)
		{
			alpha += 1.0f / 30;
		}
		else if (animationTimer <= 60)
		{
			alpha -= 1.0f / 30;
		}
		else if (animationTimer > 60)
		{
			animationTimer = 0;
			animationFlag = false;
		}
	}
}

void SceneChangeAnimation::Draw()
{
	animationSprite->DrawSprite2D({ 640,360 }, { 0.0f,0.0f ,0.0f ,alpha }, { 1280,720 });
}

const bool& SceneChangeAnimation::GetAnimationFlag()
{
	return animationFlag;
}

const float& SceneChangeAnimation::GetAnimationTimer()
{
	return animationTimer;
}

void SceneChangeAnimation::SetAnimationFlag(const bool animationFlag)
{
	this->animationFlag = animationFlag;
}

SceneChangeAnimation* SceneChangeAnimation::GetInstance()
{
	static SceneChangeAnimation instance;
	return &instance;
}
