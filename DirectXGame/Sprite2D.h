#pragma once
#include"myMath.h"
#include"DirectXBase.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"DrawCommon.h"
#include<array>
#include"Pipeline.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"SpriteCommon.h"

class Sprite2D
{
private:

	HRESULT result;
	char PADING[4];

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//���_�}�b�v
	PosUvColor* vertMap;

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;

	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffMaterial;

	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4 constBuffMap;

	//�v���W�F�N�V�����s��
	static myMath::Matrix4 matProjection;

	int blendMode = (int)BlendMode::Alpha;//�����l����������

	TextureData* texture;

public:

	Sprite2D() {}
	virtual ~Sprite2D() {}

	static void StaticInitialize();

	/// <summary>
	/// �X�v���C�g�̏���������(2D)
	/// </summary>
	/// <param name="handle">�e�N�X�`���̃n���h��</param>
	void Sprite2DInitialize(uint32_t handle);

	/// <summary>
	/// �X�v���C�g�̕`��(2D)
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">�傫��(�����l:{ 1.0f,1.0f })</param>
	/// <param name="rotation">��](�����l:0.0f)</param>
	/// <param name="anchorpoint">���S�_(�����l:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X���](�����l:false)</param>
	/// <param name="flipY">Y���](�����l:false)</param>
	void DrawSprite2D(myMath::Vector2 position, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �X�v���C�g�̐؂蔲���`��(2D)
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="clipCenter">�؂��肷�钆�S���W</param>
	/// <param name="clipRadius">�؂��肷�锼�a</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">�傫��(�����l:{ 1.0f,1.0f })</param>
	/// <param name="rotation">��](�����l:0.0f)</param>
	/// <param name="flipX">X���](�����l:false)</param>
	/// <param name="flipY">Y���](�����l:false)</param>
	void DrawSpriteClip2D(myMath::Vector2 position, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ���A�ԃX�v���C�g�`��(2D)
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">�傫��(�����l:{ 1.0f,1.0f })</param>
	/// <param name="rotation">��](�����l:0.0f)</param>
	/// <param name="anchorpoint">���S�_(�����l:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X���](�����l:false)</param>
	/// <param name="flipY">Y���](�����l:false)</param>
	void DrawAnimationSpriteX2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c�A�ԃX�v���C�g�`��(2D)
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">�傫��(�����l:{ 1.0f,1.0f })</param>
	/// <param name="rotation">��](�����l:0.0f)</param>
	/// <param name="anchorpoint">���S�_(�����l:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X���](�����l:false)</param>
	/// <param name="flipY">Y���](�����l:false)</param>
	void DrawAnimationSpriteY2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c���A�ԃX�v���C�g�`��(2D)
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="sheetsNumX">���̖���</param>
	/// <param name="sheetsNumY">�c�̖���</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">�傫��(�����l:{ 1.0f,1.0f })</param>
	/// <param name="rotation">��](�����l:0.0f)</param>
	/// <param name="anchorpoint">���S�_(�����l:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X���](�����l:false)</param>
	/// <param name="flipY">Y���](�����l:false)</param>
	void DrawAnimationSpriteXY2D(myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g(2D)
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetSprite2DBlendMode(BlendMode mode);

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
};