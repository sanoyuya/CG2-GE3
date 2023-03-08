#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"myMath.h"

class EngineOP :public BaseScene
{
private:

	std::unique_ptr<Sprite>engineLogo;
	uint32_t engineLogoTex = 0;
	myMath::Vector2 center = { 640,360 };
	myMath::Vector4 logoColor = { 0.0f,0.0f,0.0f,0.0f };

	std::unique_ptr<Sprite>back;
	uint32_t backTex = 0;

	//�A�j���[�V�����֘A
	uint16_t animationTimer = 0;
	uint16_t animationEndTime = 180;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;
};