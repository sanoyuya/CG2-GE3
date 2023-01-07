#pragma once
#include<Windows.h>
#include "InputManager.h"
#include "DirectX_.h"
#include "WindowsApp.h"
#include"FPS.h"
#include"myMath.h"
#include"GameScene.h"
#include <memory>
#include"TextureManager.h"
#include"Sprite2D.h"
#include "AudioManager.h"
#include"Model.h"
#include"SpriteCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

//�Q�[���S��
class MyGame
{
private:

	WindowsApp* windowsApp = nullptr;
	std::unique_ptr<FPS>fps;
	DirectX_* directX = nullptr;
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;
	TextureManager* textureManager = nullptr;
	std::unique_ptr<GameScene>gameScene;

public:

	//����������
	void Initialize();

	//�I������
	void Destroy();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();
};