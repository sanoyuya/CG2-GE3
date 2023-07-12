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

	HRESULT result_ = S_OK;
	char PADING_[4] = {};

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//���_�}�b�v
	PosUvColor* vertMap_ = {};

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer_ = {};

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap_ = 0;

	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffMaterial_ = {};

	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4 constBuffMap_ = {};

	//�v���W�F�N�V�����s��
	static myMath::Matrix4 matProjection_;

	BlendMode blendMode_ = BlendMode::Alpha;//�����l����������

	TextureData* texture_ = {};

public:

	Sprite2D() {}
	virtual ~Sprite2D() {}

	/// <summary>
	/// �ÓI����������
	/// </summary>
	/// <param name="windowsApp">windowsApp�̃|�C���^</param>
	static void StaticInitialize(WindowsApp* windowsApp);

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
	void SetSprite2DBlendMode(const BlendMode& mode);

private:

	/// <summary>
	/// �o�b�t�@�̐�������
	/// </summary>
	void CreateBuff();

	/// <summary>
	/// �s��v�Z
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">�p�x</param>
	void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
};