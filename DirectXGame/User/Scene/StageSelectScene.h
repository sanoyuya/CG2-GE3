#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Retention.h"
#include"InputManager.h"

class StageSelectScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input_ = nullptr;

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

	uint16_t stageNum_ = 0;
	const uint16_t minStage = 0;
	const uint16_t maxStage = 3;

	std::unique_ptr<Sprite>stageNumSprite_;
	uint32_t stageNumSpriteTex_ = 0;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

private:

	void Select();
};