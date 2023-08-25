#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"

class DemoScene:public BaseScene
{
private:

	std::unique_ptr<Camera>camera_;

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

	std::unique_ptr<Model>model_;
	Transform modelTrans_;
	uint32_t modelTex_;

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

