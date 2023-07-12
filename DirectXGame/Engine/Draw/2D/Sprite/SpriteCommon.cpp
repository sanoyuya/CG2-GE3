#include "SpriteCommon.h"

Microsoft::WRL::ComPtr<ID3D12Device>SpriteCommon::sDevice_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>SpriteCommon::sCmdList_;
Blob SpriteCommon::sBlob_;//�V�F�[�_�I�u�W�F�N�g
std::array<PipelineSet, 6> SpriteCommon::sPip_;

void SpriteCommon::StaticInitialize()
{
	sDevice_ = DirectXBase::GetInstance()->GetDevice();
	sCmdList_ = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateSpritePipline(sBlob_, (BlendMode)i, sDevice_.Get(), sPip_);
	}
}

void SpriteCommon::LoadShader()
{
	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_.vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Sprite/SpriteVS.hlsl", "main", "vs_5_0", sBlob_.vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_.ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Sprite/SpritePS.hlsl", "main", "ps_5_0", sBlob_.ps.Get());
}

void SpriteCommon::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		sCmdList_->SetPipelineState(sPip_[0].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		sCmdList_->SetPipelineState(sPip_[1].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		sCmdList_->SetPipelineState(sPip_[2].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		sCmdList_->SetPipelineState(sPip_[3].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		sCmdList_->SetPipelineState(sPip_[4].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		sCmdList_->SetPipelineState(sPip_[5].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[5].rootSignature.Get());

		break;
	}
}

void SpriteCommon::DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff)
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	sCmdList_->SetGraphicsRootConstantBufferView(0, constBuff->GetAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	sCmdList_->SetDescriptorHeaps(1, textureData->srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData->gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	sCmdList_->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	sCmdList_->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	sCmdList_->DrawIndexedInstanced(6, 1, 0, 0, 0);
}