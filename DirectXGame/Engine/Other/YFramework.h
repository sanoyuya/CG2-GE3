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

	std::wstring title = L"";
	float window_width = 0.0f;//����
	float window_height = 0.0f;//�c��

	myMath::Vector4 windowColor = { 0.0f ,0.0f ,0.0f ,0.0f };

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
	void SetWindowData(const std::string& title_ = "DirectXGame", const float width = 1280.0f, const float height = 720.0f);

	void SetWindowColor(const myMath::Vector4& color = { 0.1f,0.25f,0.5f,0.0f });

	//���s����
	void Run();
};