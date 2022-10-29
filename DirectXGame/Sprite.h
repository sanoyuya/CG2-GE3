#pragma once
#include"myMath.h"
#include"DirectX_.h"
#include"WindowsApp.h"
#include"TextureManager.h"

struct PosUvColor
{
	myMath::Vector3 pos;//���W
	myMath::Vector2 uv;//uv���W
	myMath::Vector4 color;//�F
};

class Sprite
{
private:
	HRESULT result;
	char PADING[4];
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList = nullptr;

	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//���_�}�b�v
	PosUvColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�v���W�F�N�V�����s��
	myMath::Matrix4 matProjection;

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4* constBuffMap = nullptr;

public:
	Sprite();
	~Sprite();
	void Initialize();
	void Draw(TextureData& textureData,myMath::Vector3 position, myMath::Vector3 scale, myMath::Vector3 rotation, myMath::Vector3 anchorpoint);

	void CreateVertexIndexBuffer();
	void CreateConstBuff();
};