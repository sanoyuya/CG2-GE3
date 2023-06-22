#include "PostEffect.h"
#include <d3dx12.h>

const float PostEffect::sClearColor_[4] = { 0.25f,0.5f,0.1f,0.0f };//�΂��ۂ��F
myMath::Matrix4 PostEffect::matProjection_;
std::array <Blob, 5> PostEffect::sBlob_;//�V�F�[�_�I�u�W�F�N�g
std::array <PipelineSet, 5> PostEffect::sPip_;

void PostEffect::Initialize(WindowsApp* windowsApp)
{
	//�o�b�t�@�̍쐬
	CreateBuff();
	
	VertSetting();
	//texBuff_�̐���
	CreateTexBuff(windowsApp);
	//SRV�̍쐬
	CreateSRV();
	//RTV�̍쐬
	CreateRTV();
	//�[�x�o�b�t�@�̐���
	CreateDepth(windowsApp);
	//DSV�̍쐬
	CreateDSV();
	//�p�C�v���C���̐���
	CreatePipline();
}

void PostEffect::Draw()
{
	matProjection_ = myMath::MakeIdentity();
	constBuffMap_ = matProjection_;
	constBuffMaterial_->Update(&constBuffMap_);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[0].pipelineState.Get());
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());

	//�`��R�}���h
	DrawCommand();
}

void PostEffect::VertSetting()
{
	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-1.0f,1.0f,0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{1.0f,-1.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{1.0f,1.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
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
}

void PostEffect::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(PosUvColor));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void PostEffect::CreateTexBuff(WindowsApp* windowsApp)
{
	//�e�N�X�`�����\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, sClearColor_);
	//�e�N�X�`���o�b�t�@�̐���
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&clearValue,
		IID_PPV_ARGS(&texBuff_));
	assert(SUCCEEDED(result));

	////��f��(1280*720=921600�s�N�Z��)
	//const uint32_t pixelCount = static_cast<uint32_t>(windowsApp->GetWidth() * windowsApp->GetHeight());
	////��f1�s���̃f�[�^�T�C�Y
	//const uint32_t rowPitch = sizeof(uint32_t) * static_cast<uint32_t>(windowsApp->GetWidth());
	////�摜�S�̂̃f�[�^�T�C�Y
	//const uint32_t depthPitch = rowPitch * static_cast<uint32_t>(windowsApp->GetHeight());
	////�摜�C���[�W
	//UINT* img = new UINT[pixelCount];
	//for (uint32_t i = 0; i < pixelCount; i++)
	//{
	//	img[i] = 0xff0000ff;
	//}

	////�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	//result = texBuff_->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
	//assert(SUCCEEDED(result));
	//delete[]img;
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

void PostEffect::CreatePipline()
{
	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreatePostEffectPipline(sBlob_[0], sPip_[0]);
	}
}

void PostEffect::LoadShader()
{
	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[0].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[0].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());
}

void PostEffect::DrawCommand()
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	DirectXBase::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	auto vbView = vertexBuffer_->GetView();
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	DirectXBase::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial_.get()->GetAddress());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = handle_.gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	auto ibView = indexBuffer_->GetView();
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	DirectXBase::GetInstance()->GetCommandList()->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	DirectXBase::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void PostEffect::CreateSRV()
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