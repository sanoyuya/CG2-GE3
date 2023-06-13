#include "Model.h"
#include"DirectXBase.h"
#include"Obj.h"
#include"AssimpLoder.h"

#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"

Microsoft::WRL::ComPtr<ID3D12Device> Model::sDevice_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Model::sCmdList_;
std::vector<std::string>Model::sFilePaths_;
std::unordered_map<std::string, std::unique_ptr<ModelData>> Model::sModelDatas_;
LightManager* Model::sLightManager_ = nullptr;
uint32_t Model::sModelCount_;
std::array <Blob, 5> Model::sBlob_;//�V�F�[�_�I�u�W�F�N�g
std::array <std::array<PipelineSet, 6>, 5> Model::sPip_;

void Model::StaticInitialize()
{
	sDevice_ = DirectXBase::GetInstance()->GetDevice();
	sCmdList_ = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateBasicModelPipline(sBlob_[0], (BlendMode)i, sDevice_.Get(), sPip_[0]);//Basic�V�F�[�_�[�p
		Pipeline::CreatePhongModelPipline(sBlob_[1], (BlendMode)i, sDevice_.Get(), sPip_[1]);//Phong�V�F�[�_�[�p
		Pipeline::CreatePhongModelPipline(sBlob_[2], (BlendMode)i, sDevice_.Get(), sPip_[2]);//Toon�V�F�[�_�[�p
		Pipeline::CreatePhongModelPipline(sBlob_[3], (BlendMode)i, sDevice_.Get(), sPip_[3]);//�������C�g�p
	}

	sFilePaths_.resize(sMaxModel_);
}

void Model::SetLight(LightManager* lightManager_)
{
	Model::sLightManager_ = lightManager_;
}

void Model::StaticDestory()
{
	Model::sDevice_ = nullptr;
	Model::sCmdList_ = nullptr;
	Model::sModelDatas_.clear();
}

void Model::LoadShader()
{
#pragma region Basic�V�F�[�_�[�p

	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[0].vs = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[0].ps = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());

#pragma endregion Basic�V�F�[�_�[�p

#pragma region Phong�V�F�[�_�[�p

	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[1].vs = DrawCommon::ShaderCompile(L"Resources/shaders/PhongVS.hlsl", "main", "vs_5_0", sBlob_[1].vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[1].ps = DrawCommon::ShaderCompile(L"Resources/shaders/PhongPS.hlsl", "main", "ps_5_0", sBlob_[1].ps.Get());

#pragma endregion Phong�V�F�[�_�[�p

#pragma region Toon�V�F�[�_�[�p

	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[2].vs = DrawCommon::ShaderCompile(L"Resources/shaders/ToonVS.hlsl", "main", "vs_5_0", sBlob_[2].vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[2].ps = DrawCommon::ShaderCompile(L"Resources/shaders/ToonPS.hlsl", "main", "ps_5_0", sBlob_[2].ps.Get());

#pragma endregion Toon�V�F�[�_�[�p

#pragma region �������C�g�p

	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[3].vs = DrawCommon::ShaderCompile(L"Resources/shaders/RimLightVS.hlsl", "main", "vs_5_0", sBlob_[3].vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_[3].ps = DrawCommon::ShaderCompile(L"Resources/shaders/RimLightPS.hlsl", "main", "ps_5_0", sBlob_[3].ps.Get());

#pragma endregion �������C�g�p
}

void Model::PiplineSet(BlendMode bMode,ShaderMode sMode)
{
	switch (bMode)
	{
	case BlendMode::None:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][0].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][0].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][0].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][0].rootSignature.Get());

			break;
		}

		break;

	case BlendMode::Alpha:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][1].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][1].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][1].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][1].rootSignature.Get());

			break;
		}

		break;

	case BlendMode::Add:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][2].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][2].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][2].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][2].rootSignature.Get());

			break;
		}

		break;

	case BlendMode::Sub:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][3].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][3].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][3].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][3].rootSignature.Get());

			break;
		}

		break;

	case BlendMode::Mul:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][4].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][4].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][4].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][4].rootSignature.Get());

			break;
		}

		break;

	case BlendMode::Inv:

		switch (sMode)
		{
		case ShaderMode::Basic:

			sCmdList_->SetPipelineState(sPip_[0][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[0][5].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			sCmdList_->SetPipelineState(sPip_[1][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[1][5].rootSignature.Get());

			break;
		case ShaderMode::Toon:

			sCmdList_->SetPipelineState(sPip_[2][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[2][5].rootSignature.Get());

			break;
		case ShaderMode::RimLight:

			sCmdList_->SetPipelineState(sPip_[3][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[3][5].rootSignature.Get());

			break;
		}

		break;
	}
}

uint32_t Model::CreateObjModel(const std::string& filePath, bool smoothing)
{
	std::string path = filePath;

	path += smoothing ? " : true" : " : false";

	//���ǂݍ��񂾂��Ƃ�����t�@�C���͂��̂܂ܕԂ�
	auto itr = find_if(sModelDatas_.begin(), sModelDatas_.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});

	if (itr == sModelDatas_.end())
	{
		uint32_t modelHandle = sModelCount_;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		Obj::Create(filePath.c_str(), smoothing, data.get());

		data->modelHandle = sModelCount_;

		data->filePath = path;

		sModelDatas_[path] = std::move(data);

		sFilePaths_[sModelCount_] = path;

		sModelCount_++;

		return modelHandle;
	}
	else
	{
		uint32_t modelHandle = sModelDatas_[path]->modelHandle;

		return modelHandle;
	}
}

void Model::DrawModel(Transform* transform, myMath::Vector4 color)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = modelData_->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = modelData_->indexBuffer->GetView();

	tmp_ = color;
	constantBuff_->Update(&tmp_);

	PiplineSet(static_cast<BlendMode>(blendMode_),static_cast<ShaderMode>(shaderMode_));

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	sCmdList_->IASetIndexBuffer(&ibView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	sCmdList_->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	sCmdList_->SetGraphicsRootConstantBufferView(1, modelData_->constBuffMaterial->GetAddress());
	//���[�g�p�����[�^2�ԂɐF����ݒ�
	sCmdList_->SetGraphicsRootConstantBufferView(2, constantBuff_->GetAddress());

	//���C�g�̕`��
	if (shaderMode_ != ShaderMode::Basic)
	{
		//���[�g�p�����[�^2�ԂɃ��C�g����ݒ�
		sLightManager_->Draw(sCmdList_.Get(), 4);
	}

	// SRV�q�[�v�̐ݒ�R�}���h
	sCmdList_->SetDescriptorHeaps(1, modelData_->textureData->srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^3�Ԃɐݒ�
	sCmdList_->SetGraphicsRootDescriptorTable(3, modelData_->textureData->gpuHandle);

	// �`��R�}���h
	sCmdList_->DrawIndexedInstanced(modelData_->maxIndex, 1, 0, 0, 0);
}

const myMath::Matrix4& Model::GetMatWorld()
{
	return modelData_->matWorld;
}

const std::vector<PosNormalUv> Model::GetVertices()
{
	return modelData_->vertices;
}

const std::vector<uint32_t> Model::GetIndices()
{
	return modelData_->indices;
}

void Model::SetModel(const uint32_t& modelHandle)
{
	modelData_ = sModelDatas_[sFilePaths_[modelHandle]].get();
}

void Model::SetModelBlendMode(const BlendMode& mode)
{
	blendMode_ = mode;
}

void Model::SetShaderMode(const ShaderMode& mode)
{
	shaderMode_ = mode;
}

Model::Model()
{
	constantBuff_ = std::make_unique<ConstantBuffer>();
	constantBuff_->Create(sizeof(myMath::Vector4));
}

Model::~Model()
{

}