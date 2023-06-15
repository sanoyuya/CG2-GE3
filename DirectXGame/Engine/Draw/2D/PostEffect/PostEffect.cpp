#include "PostEffect.h"
#include <d3dx12.h>

void PostEffect::Initialize(WindowsApp* windowsApp)
{
	//�e�N�X�`���ǂݍ���
	tex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	//���N���X�Ƃ��Ă̏�����
	Sprite2D::Sprite2DInitialize(tex_);

	CreateTexBuff(windowsApp);

	CreateDescHeap();

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
	// ���\�[�X�𐶐�
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
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

	//�f�X�N���v�^�q�[�v��SRV�쐬
	handle_ = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(), &srvDesc, handle_.cpuHandle);
}