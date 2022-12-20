#pragma once
#include"myMath.h"
#include"DirectX_.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"DrawCommon.h"
#include<array>
#include"Pipeline.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"

class Sprite2D
{
private:

	HRESULT result;
	char PADING[4];
	static Microsoft::WRL::ComPtr<ID3D12Device>device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//���_�}�b�v
	PosUvColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�v���W�F�N�V�����s��
	static myMath::Matrix4 matProjection;

	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffMaterial;

	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4 constBuffMap;

	static Blob blob;//�V�F�[�_�I�u�W�F�N�g

	static std::array<PipelineSet, 6> pip;

	int blendMode = (int)BlendMode::Alpha;//�����l����������

	TextureData* texture;

public:

	Sprite2D() {}
	virtual ~Sprite2D() {}

	static void StaticInitialize();

	/// <summary>
	/// �X�v���C�g�̏���������
	/// </summary>
	void Sprite2DInitialize(uint32_t handle);

	/// <summary>
	/// �X�v���C�g�̕`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">��]</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawSprite2D(myMath::Vector2 position, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �X�v���C�g�̐؂蔲���`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="clipCenter">�؂��钆�S���W</param>
	/// <param name="clipRadius">�؂���傫��(���a)</param>
	/// <param name="color">�F</param> 
	/// <param name="scale">�傫��</param> 
	/// <param name="rotation">��]</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawSpriteClip2D(myMath::Vector2 position, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ���A�ԃX�v���C�g�`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">��]</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteX2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c�A�ԃX�v���C�g�`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="sheetsNum">����</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">��]</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteY2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �c���A�ԃX�v���C�g�`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="sheetsNumX">���̖���</param>
	/// <param name="sheetsNumY">�c�̖���</param>
	/// <param name="nowNum">�����ڂ�</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">��]</param>
	/// <param name="anchorpoint">���S�_</param>
	/// <param name="flipX">X���]</param>
	/// <param name="flipY">Y���]</param>
	void DrawAnimationSpriteXY2D(myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetSpriteBlendMode(BlendMode mode);

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	static void LoadShader();
	void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
	void BlendSet(BlendMode mode);
};