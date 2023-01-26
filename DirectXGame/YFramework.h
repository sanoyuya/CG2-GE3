#pragma once
#include<Windows.h>
#include "InputManager.h"
#include "DirectXBase.h"
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
#include<memory>
#include"ImGuiManager.h"

#pragma comment(lib, "d3dcompiler.lib")

//�Q�[���S��
class YFramework
{
protected:

	std::wstring title;
	float window_width = 0;//����
	float window_height = 0;//�c��

	bool endRequest = false;

	WindowsApp* windowsApp = nullptr;
	std::unique_ptr<FPS>fps;
	DirectXBase* directX = nullptr;
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;
	TextureManager* textureManager = nullptr;
	ImGuiManager* imGuiManager = nullptr;

public:

	virtual ~YFramework() = default;

	//����������
	virtual void Initialize();

	//�I������
	virtual void Destroy();

	//�X�V����
	virtual void Update();

	//�`�揈��
	virtual void Draw() = 0;

	virtual bool& GetEndRequest();

public:

	/// <summary>
	/// �E�B���h�E�̐ݒ�
	/// </summary>
	/// <param name="title">�^�C�g���o�[�̖��O</param>
	/// <param name="width">�E�B���h�E�̉���</param>
	/// <param name="height">�E�B���h�E�̏c��</param>
	void SetWindowData(const std::string& title = "DirectXGame", const int width = 1280, const int height = 720);

	//���s����
	void Run();
};