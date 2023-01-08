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
#include"YFramework.h"
#include"SceneManager.h"

#pragma comment(lib, "d3dcompiler.lib")

//�Q�[���S��
class MyGame :public YFramework
{
private:

	WindowsApp* windowsApp = nullptr;
	std::unique_ptr<FPS>fps;
	DirectX_* directX = nullptr;
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;
	TextureManager* textureManager = nullptr;
	//std::unique_ptr<GameScene>gameScene;
	SceneManager* sceneManager = nullptr;

	static bool endRequest;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	static const bool& GetEndRequest();
};