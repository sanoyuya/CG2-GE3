#include "Sprite3D.h"

void Sprite3D::Sprite3DInitialize(uint32_t handle)
{
	texture = TextureManager::GetTextureData(handle);
	CreateVertexIndexBuffer();
	CreateConstBuff();
}

void Sprite3D::DrawSprite3D(Camera* camera, Transform& transform, BillboardFlag flag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture->width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture->width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture->height) * isFlipY;

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
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	Update(camera, transform, flag);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SpriteCommon::BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	//�`��R�}���h
	SpriteCommon::DrawCommand(texture, vbView, ibView, constBuffMaterial.get());
}

void Sprite3D::DrawSpriteClip3D(Camera* camera, Transform& transform, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, BillboardFlag billboardFlag, myMath::Vector4 color, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = -clipRadius.x * isFlipX;
	float right = clipRadius.x * isFlipX;
	float top = -clipRadius.y * isFlipY;
	float bottom = clipRadius.y * isFlipY;

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(clipCenter.x - clipRadius.x) / texture->width,(clipCenter.y - clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{(clipCenter.x - clipRadius.x) / texture->width,(clipCenter.y + clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{(clipCenter.x + clipRadius.x) / texture->width,(clipCenter.y - clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{(clipCenter.x + clipRadius.x) / texture->width,(clipCenter.y + clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	Update(camera, transform, billboardFlag);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SpriteCommon::BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	//�`��R�}���h
	SpriteCommon::DrawCommand(texture, vbView, ibView, constBuffMaterial.get());
}

void Sprite3D::DrawAnimationSpriteX3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY3D(camera, transform, sheetsNum, 1, nowNum, billboardFlag, color, anchorpoint, flipX, flipY);
}

void Sprite3D::DrawAnimationSpriteY3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY3D(camera, transform, 1, sheetsNum, nowNum, billboardFlag, color, anchorpoint, flipX, flipY);
}

void Sprite3D::DrawAnimationSpriteXY3D(Camera* camera, Transform& transform, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture->width / sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture->width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture->height / sheetsNumY) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture->height / sheetsNumY) * isFlipY;

	uint16_t animationXYNum = sheetsNumX * sheetsNumY;//������(�����v)
	uint16_t x = nowNum % sheetsNumX;
	uint16_t y = nowNum / sheetsNumX;

	if (nowNum + 1 > animationXYNum)
	{
		nowNum = 0;//0���ڂɖ߂�����
	}

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(float)x / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{(float)x / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{((float)x + 1) / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{((float)x + 1) / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	Update(camera, transform, billboardFlag);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SpriteCommon::BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	//�`��R�}���h
	SpriteCommon::DrawCommand(texture, vbView, ibView, constBuffMaterial.get());
}

void Sprite3D::SetSprite3DBlendMode(BlendMode mode)
{
	blendMode = static_cast<int>(mode);
}

void Sprite3D::CreateVertexIndexBuffer()
{
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

void Sprite3D::CreateConstBuff()
{
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(myMath::Matrix4));
}

void Sprite3D::Update(Camera* camera, Transform transform, BillboardFlag flag)
{
	myMath::Matrix4 mTrans, mRot, mScale;

	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case BillboardFlag::NonBillboard:
		transform.matWorld = mScale * mRot * mTrans * camera->GetMatViewInverse() * camera->GetMatProjection();
		break;
	case BillboardFlag::AllBillboard:

		{
			myMath::Matrix4 Allmat = camera->GetMatView();

			Allmat.m[3][0] = 0;
			Allmat.m[3][1] = 0;
			Allmat.m[3][2] = 0;
			Allmat.m[3][3] = 1;

			transform.matWorld = mScale * mRot * Allmat * mTrans * camera->GetMatViewInverse() * camera->GetMatProjection();
			break;
		}

	case BillboardFlag::XBillboard:

		{
			myMath::Matrix4 Xmat = camera->GetMatView();

			Xmat.m[1][0] = 0;
			Xmat.m[1][1] = 1;
			Xmat.m[1][2] = 0;
			Xmat.m[1][3] = 0;

			Xmat.m[3][0] = 0;
			Xmat.m[3][1] = 0;
			Xmat.m[3][2] = 0;
			Xmat.m[3][3] = 1;

			transform.matWorld = mScale * mRot * Xmat * mTrans * camera->GetMatViewInverse() * camera->GetMatProjection();
			break;
		}

	case BillboardFlag::YBillboard:

		{
			myMath::Matrix4 Ymat = camera->GetMatView();

			Ymat.m[0][0] = 1;
			Ymat.m[0][1] = 0;
			Ymat.m[0][2] = 0;
			Ymat.m[0][3] = 0;

			Ymat.m[3][0] = 0;
			Ymat.m[3][1] = 0;
			Ymat.m[3][2] = 0;
			Ymat.m[3][3] = 1;


			transform.matWorld = mScale * mRot * Ymat * mTrans * camera->GetMatViewInverse() * camera->GetMatProjection();
			break;
		}

	case BillboardFlag::XYBillboard:

		{
			myMath::Matrix4 XYmat = camera->GetMatView();

			XYmat.m[2][0] = 0;
			XYmat.m[2][1] = 0;
			XYmat.m[2][2] = 1;
			XYmat.m[2][3] = 0;

			XYmat.m[3][0] = 0;
			XYmat.m[3][1] = 0;
			XYmat.m[3][2] = 0;
			XYmat.m[3][3] = 1;

			transform.matWorld = mScale * mRot * XYmat * mTrans * camera->GetMatViewInverse() * camera->GetMatProjection();
			break;
		}
	}

	transform.Update();
	constBuffMap = transform.matWorld;
	constBuffMaterial->Update(&constBuffMap);
}