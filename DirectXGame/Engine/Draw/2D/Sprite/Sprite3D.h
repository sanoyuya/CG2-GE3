#pragma once
#include"DrawCommon.h"
#include<memory>
#include"SpriteCommon.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "TextureManager.h"
#include"Camera.h"
#include"Transform.h"

enum class BillboardFlag
{
	NonBillboard,//�r���{�[�h�����Ȃ�
	AllBillboard,//���ׂđł�����
	XBillboard,//X����ł�����
	YBillboard,//Y����ł�����
	XYBillboard//Z����ł�����
};

class Sprite3D
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

	BlendMode blendMode_ = BlendMode::Alpha;//�����l����������

	TextureData* texture_ = {};

public:

	Sprite3D() {}
	virtual ~Sprite3D() {}

	/// <summary>
	/// �X�v���C�g�̏���������(3D)
	/// </summary>
	void Sprite3DInitialize(uint32_t handle);

	/// <summary>
	/// �X�v���C�g�̕`��(3D)
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="billboardFlag">�r���{�[�h�̎��(�����l:NonBillboard)</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">���S�_(�����l:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawSprite3D(Camera* camera, Transform& transform, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �X�v���C�g�̐؂���`��(3D)
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="clipCenter">�؂��肷�钆�S���W</param>
	/// <param name="clipRadius">�؂��肷�锼�a</param>
	/// <param name="billboardFlag">�r���{�[�h�̎��(�����l:NonBillboard)</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawSpriteClip3D(Camera* camera, Transform& transform, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ���A�ԃX�v���C�g�`��(3D)
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="billboardFlag">�r���{�[�h�̎��(�����l:NonBillboard)</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteX3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c�A�ԃX�v���C�g�`��(3D)
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="billboardFlag">�r���{�[�h�̎��(�����l:NonBillboard)</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteY3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c���A�ԃX�v���C�g�`��(3D)
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="sheetsNumX">���̖���</param>
	/// <param name="sheetsNumY">�c�̖���</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="billboardFlag">�r���{�[�h�̎��(�����l:NonBillboard)</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteXY3D(Camera* camera, Transform& transform, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g(3D)
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetSprite3DBlendMode(const BlendMode& mode);

private:

	/// <summary>
	/// �o�b�t�@�̐�������
	/// </summary>
	void CreateBuff();

	/// <summary>
	/// �s��v�Z
	/// </summary>
	/// <param name="camera">�J�����̃|�C���^</param>
	/// <param name="transform">�g�����X�t�H�[��</param>
	/// <param name="flag">�r���{�[�h�̎��</param>
	void Update(Camera* camera, Transform transform,BillboardFlag flag);
	//void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
};

