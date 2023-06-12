#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"myMath.h"

class EngineOP :public BaseScene
{
private:

	std::unique_ptr<Sprite>engineLogo_;
	uint32_t engineLogoTex_ = 0;
	myMath::Vector2 center_ = { 640,360 };
	myMath::Vector4 logoColor_ = { 0.0f,0.0f,0.0f,0.0f };

	std::unique_ptr<Sprite>back_;
	uint32_t backTex_ = 0;

	//�A�j���[�V�����֘A
	uint16_t animationTimer_ = 0;
	uint16_t animationEndTime_ = 180;

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