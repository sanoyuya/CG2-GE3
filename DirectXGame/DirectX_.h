#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <d3dcompiler.h>
#include<DirectXTex.h>
#include <DirectXMath.h>
#include"myMath.h"
#include<wrl.h>

using namespace myMath;
using namespace DirectX;

class DirectX_
{
public:
	//�G�C���A�X�e���v���[�g
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	const int window_width = 1280;//����
	const int window_height = 720;//�c��

	HRESULT result;
	ComPtr <ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//IDXGISwapChain1��ComPtr��p��
	ComPtr<IDXGISwapChain1>swapChain1;
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>>backBuffers;
	//�t�F���X�̐���
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;



	//�`�揉��������
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};

	ComPtr<ID3D12Resource> constBuffMaterial;

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	// ���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff;

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap = nullptr;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//�C���f�b�N�X�o�b�t�@�̐���
	ComPtr<ID3D12Resource> indexBuff = nullptr;

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap = nullptr;

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

	// �u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];// RBGA�S�Ẵ`�����l����`��

	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob = nullptr;

	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState = nullptr;




	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D�ϊ��s��
	};

	////�萔�o�b�t�@�̐���
	//ID3D12Resource* constBuffTransform0 = nullptr;
	//ConstBufferDataTransform* constMapTransform0 = nullptr;

	//ID3D12Resource* constBuffTransform1 = nullptr;
	//ConstBufferDataTransform* constMapTransform1 = nullptr;

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc_{};




	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};


	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//�F(RGBA)
	};

	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	// �V�U�[��`
	D3D12_RECT scissorRect{};

	//���_�f�[�^�̍\����
	struct Vertex {
		XMFLOAT3 pos;		//xyz���W
		XMFLOAT3 normal;	//�@���x�N�g��
		XMFLOAT2 uv;		//uv���W
	};

	//���_�f�[�^
	Vertex vertices[24] = {
		//  x	  y   z		 u	  v
		//�O
		{{-5.0f,-5.0f,-5.0f},{}, {0.0f,1.0f}},//����
		{{-5.0f,5.0f,-5.0f},{},{0.0f,0.0f}},//����
		{{5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},//�E��
		{{5.0f,5.0f,-5.0f},{},{1.0f,0.0f}},//�E��
		//��(�O�ʂ�Z���W�̕������t)
		{{-5.0f,-5.0f,5.0f},{},{0.0f,1.0f}},//����
		{{-5.0f,5.0f,5.0f},{},{0.0f,0.0f}},//����
		{{5.0f,-5.0f,5.0f},{},{1.0f,1.0f}},//�E��
		{{5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//�E��
		//��
		{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//����
		{{-5.0f,-5.0f,5.0f},{},{0.0f,0.0f}},//����
		{{-5.0f,5.0f,-5.0f},{},{1.0f,1.0f}},//�E��
		{{-5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//�E��
		//�E(���ʂ�X���W�̕������t)
		{{5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//����
		{{5.0f,-5.0f,5.0f},{},{0.0f,0.0f}},//����
		{{5.0f,5.0f,-5.0f},{},{1.0f,1.0f}},//�E��
		{{5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//�E��
		//��
		{{-5.0f,-5.0f,5.0f},{},{0.0f,1.0f}},//����
		{{-5.0f,-5.0f,-5.0f},{},{0.0f,0.0f}},//����
		{{5.0f,-5.0f,5.0f},{},{1.0f,1.0f}},//�E��
		{{5.0f,-5.0f,-5.0f},{},{1.0f,0.0f}},//�E��
		//��(��ʂ�Y���W�̕������t)
		{{-5.0f,5.0f,5.0f},{},{0.0f,1.0f}},//����
		{{-5.0f,5.0f,-5.0f},{},{0.0f,0.0f}},//����
		{{5.0f,5.0f,5.0f},{},{1.0f,1.0f}},//�E��
		{{5.0f,5.0f,-5.0f},{},{1.0f,0.0f}},//�E��
	};

	//�C���f�b�N�X�f�[�^
	unsigned short indices[36] = {
		//�O
		0,1,2,//�O�p�`1��
		2,1,3,//�O�p�`2��
		//��(�O�̖ʂ�4���Z)
		4,6,5,//�O�p�`1��
		7,5,6,//�O�p�`2��
		//��(�O�̖ʂ�4���Z)
		8,9,10,//�O�p�`1��
		10,9,11,//�O�p�`2��
		//�E(�O�̖ʂ�4���Z)
		12,14,13,//�O�p�`1��
		15,13,14,//�O�p�`2��
		//��(�O�̖ʂ�4���Z)
		16,17,18,//�O�p�`1��
		18,17,19,//�O�p�`2��
		//��(�O�̖ʂ�4���Z)
		20,22,21,//�O�p�`1��
		23,21,22,//�O�p�`2��
	};

	//���_�f�[�^�S�̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));


	//1.���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};



	//�e�N�X�`���}�b�s���O��������

	////�������s�N�Z����
	//const size_t textureWidth = 256;
	////�c�����s�N�Z����
	//const size_t textureHeight = 256;
	////�z��̗v�f��
	//const size_t imageDataCount = textureWidth * textureHeight;
	////�摜�C���[�W�f�[�^�z��
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];//�K����ŉ������

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	D3D12_RESOURCE_DESC textureResourceDesc2{};

	//�e�N�X�`���o�b�t�@�̐���
	ComPtr<ID3D12Resource> texBuff = nullptr;
	ComPtr<ID3D12Resource> texBuff2 = nullptr;

	//SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	//�V�F�[�_�[���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc2{};//�ݒ�\����

	//�f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//�e�N�X�`���}�b�s���O�����܂�

	





	//�[�x�o�b�t�@
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};
	ComPtr<ID3D12Resource> depthBuff = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};




	Matrix4 MATRIX4;



	//�r���[�ϊ��s��	
	XMMATRIX matView;
	float angle = 0.0f;//�J�����̉�]�p
	//�J��������
	XMFLOAT3 eye = { 0, 0, -100 };	//���_���W
	XMFLOAT3 target = { 0, 0, 0 };	//�����_���W
	XMFLOAT3 up = { 0, 1, 0 };		//������x�N�g��

	//�ˉe�ϊ��s��(�������e)
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);



	//3D�I�u�W�F�N�g�^
	struct Object3d
	{
		//�萔�o�b�t�@(�s��p)
		ComPtr<ID3D12Resource> constBuffTransform;
		//�萔�o�b�t�@�}�b�v(�s��p)
		ConstBufferDataTransform* constMapTransform;
		//�A�t�B���ϊ����
		XMFLOAT3 scale = { 1,1,1 };
		XMFLOAT3 rotation = { 0,0,0 };
		XMFLOAT3 position = { 0,0,0 };
		//���[���h�ϊ��s��
		XMMATRIX matWorld;
		//�e�I�u�W�F�N�g�ւ̃|�C���^
		Object3d* parent = nullptr;
	};

	//3D�I�u�W�F�N�g�̐�
	const size_t kObjectCount = 50;
	//3D�I�u�W�F�N�g�̔z��
	Object3d object3ds[50];

	//2���ڗp�ɕʂ̕ϐ���p�ӂ��Ă���
	TexMetadata metadata2{};
	ScratchImage scratchImg2{};

	
	
public:
	DirectX_(HWND hwnd, WNDCLASSEX w);
	DirectX_() = default;
	void DrawInitialize(HWND hwnd, WNDCLASSEX w);
	void UpdateClear();
	void UpdateEnd();
	void DrawUpdate();
	void InitializeObject3d(Object3d* object, ComPtr<ID3D12Device> device);
	void UpdateObject3d(Object3d* object, XMMATRIX& matView, XMMATRIX& matProjection);
	void DrawObject3d(Object3d* object, ComPtr<ID3D12GraphicsCommandList> commandList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);

	//�Q�b�^�[
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	const int GetWindow_width();
	const int GetWindow_height();
};