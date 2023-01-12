#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"Score.h"
#include"SceneChangeAnimation.h"
#include"AudioManager.h"

class ResultScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	AudioManager* audioManager = nullptr;

	Score* score = nullptr;

	std::unique_ptr<Sprite>resultBack;
	uint16_t resultBackTex = 0;

	std::unique_ptr<Sprite>thanks;
	uint16_t thanksTex = 0;

	std::unique_ptr<Sprite>press;
	uint16_t pressTex = 0;

	float timer = 0.0f;

	uint32_t resultBGM = 0;

public:

	//����������
	void Initialize()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	//�I������
	void Destroy()override;
};