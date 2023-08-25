#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"

class StageSelectScene :public BaseScene
{
private:

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

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