#include "PostEffect.h"

void PostEffect::Initialize()
{
	scale = { 500.0f,500.0f };
	color = { 1.0f,1.0f ,1.0f ,1.0f };

	//�e�N�X�`���ǂݍ���
	tex = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	Sprite2D::Sprite2DInitialize(tex);
}

void PostEffect::Draw()
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture_->width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture_->width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture_->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture_->height) * isFlipY;

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{0.0f,1.0f},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{1.0f,0.0f},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{1.0f,1.0f},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer_->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer_->Update(indices);

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SpriteCommon::BlendSet(blendMode_);

	//�`��R�}���h
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}