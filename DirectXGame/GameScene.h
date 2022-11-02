#pragma once

#include"InputManager.h"
#include<memory>
#include"Camera.h"
#include"Sprite.h"
#include"TextureManager.h"
#include"DrawManager.h"

class GameScene
{
private:

	//ÉNÉâÉXì«Ç›çûÇ›
	InputManager* input = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawManager>draw;
	TextureData tex;
	std::unique_ptr<DrawManager>draw2;
	TextureData tex2;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();
};