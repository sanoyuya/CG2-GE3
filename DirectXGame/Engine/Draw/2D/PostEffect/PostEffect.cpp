#include "PostEffect.h"
#include <d3dx12.h>

const float PostEffect::sClearColor_[4] = { 0.25f,0.5f,0.1f,0.0f };//�΂��ۂ��F

void PostEffect::Initialize(WindowsApp* windowsApp)
{
	//�e�N�X�`���ǂݍ���
	tex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	//���N���X�Ƃ��Ă̏�����
	Sprite2D::Sprite2DInitialize(tex_);

	//texBuff_�̐���
	CreateTexBuff(windowsApp);
	//SRV�̍쐬
	CreateDescHeap();
	//RTV�̍쐬
	CreateRTV();
	//�[�x�o�b�t�@�̐���
	CreateDepth(windowsApp);
	//DSV�̍쐬
	CreateDSV();

	scale_ = { 500.0f,500.0f };
	color_ = { 1.0f,1.0f ,1.0f ,1.0f };
}

void PostEffect::Draw()
{
	int isFlipX, isFlipY;
	if (flipX_ == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY_ == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint_.x) * texture_->width) * isFlipX;
	float right = ((1.0f - anchorpoint_.x) * texture_->width) * isFlipX;
	float top = ((0.0f - anchorpoint_.y) * texture_->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint_.y) * texture_->height) * isFlipY;

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color_.x, color_.y, color_.z, color_.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{0.0f,1.0f},{color_.x, color_.y, color_.z, color_.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{1.0f,0.0f},{color_.x, color_.y, color_.z, color_.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{1.0f,1.0f},{color_.x, color_.y, color_.z, color_.w}},//�E���C���f�b�N�X3
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

	Update(position_, scale_, rotation_);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SpriteCommon::BlendSet(blendMode_);

	//�`��R�}���h
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void PostEffect::CreateTexBuff(WindowsApp* windowsApp)
{
	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, sClearColor_);
	// ���\�[�X�𐶐�
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&clearValue,
		IID_PPV_ARGS(&texBuff_));
	assert(SUCCEEDED(result));

	//��f��(1280*720=921600�s�N�Z��)
	const uint32_t pixelCount = static_cast<uint32_t>(windowsApp->GetWidth() * windowsApp->GetHeight());
	//��f1�s���̃f�[�^�T�C�Y
	const uint32_t rowPitch = sizeof(uint32_t) * static_cast<uint32_t>(windowsApp->GetWidth());
	//�摜�S�̂̃f�[�^�T�C�Y
	const uint32_t depthPitch = rowPitch * static_cast<uint32_t>(windowsApp->GetHeight());
	//�摜�C���[�W
	UINT* img = new UINT[pixelCount];
	for (uint32_t i = 0; i < pixelCount; i++)
	{
		img[i] = 0xff0000ff;
	}

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texBuff_->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
	assert(SUCCEEDED(result));
	delete[]img;
}

void PostEffect::CreateDescHeap()
{
	//SRV�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//�f�X�N���v�^�q�[�v�����Z
	handle_ = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(), &srvDesc, handle_.cpuHandle);
}

void PostEffect::PreDrawScene(WindowsApp* windowsApp)
{
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
	//���\�[�X�o���A��ύX(�V�F�[�_�[���\�[�X->�`��\)
	DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &transition);

	//�����_�[�^�[�Q�b�g�r���[�p�f�X�N���v�^�q�[�v�̃n���h���擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH = descHeapRTV_->GetCPUDescriptorHandleForHeapStart();

	//�[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV_->GetCPUDescriptorHandleForHeapStart();

	//�����_�[�^�[�Q�b�g���Z�b�g
	DirectXBase::GetInstance()->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//�r���[�|�[�g�̐ݒ�
	auto viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, windowsApp->GetWidth(), windowsApp->GetHeight());
	DirectXBase::GetInstance()->GetCommandList()->RSSetViewports(1, &viewPort);

	//�V�U�����O��`�̐ݒ�
	auto rect = CD3DX12_RECT(0, 0, static_cast<LONG>(windowsApp->GetWidth()), static_cast<LONG>(windowsApp->GetHeight()));
	DirectXBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &rect);

	//�S��ʃN���A
	DirectXBase::GetInstance()->GetCommandList()->ClearRenderTargetView(rtvH, sClearColor_, 0, nullptr);
	//�[�x�o�b�t�@�̃N���A
	DirectXBase::GetInstance()->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::PostDrawScene()
{
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrier);
}

void PostEffect::CreateRTV()
{
	//RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV�p�f�X�N���v�^�q�[�v���쐬
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));

	//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//�f�X�N���v�^�q�[�v��RTV�쐬
	DirectXBase::GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_.Get(), &renderTargetViewDesc, descHeapRTV_->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::CreateDepth(WindowsApp* windowsApp)
{
	//�[�x�o�b�t�@���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	//�[�x�o�b�t�@����
	auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	auto properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&properties,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&depthBuff_));
	assert(SUCCEEDED(result));
}

void PostEffect::CreateDSV()
{
	//DSV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC dsvDescHeapDesc{};
	dsvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvDescHeapDesc.NumDescriptors = 1;
	//DSV�p�f�X�N���v�^�q�[�v���쐬
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&dsvDescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
	assert(SUCCEEDED(result));

	//�f�X�N���v�^�q�[�v��DSV�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DirectXBase::GetInstance()->GetDevice()->CreateDepthStencilView(depthBuff_.Get(), &dsvDesc, descHeapDSV_->GetCPUDescriptorHandleForHeapStart());
}