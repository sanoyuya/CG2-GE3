#include "Model.h"
#include"DirectX_.h"
#include"Obj.h"

Microsoft::WRL::ComPtr<ID3D12Device> Model::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Model::cmdList;
std::vector<std::string>Model::filePaths;
std::unordered_map<std::string, std::unique_ptr<ModelData>> Model::modelDatas;
uint32_t Model::modelCount;
Blob Model::blob;//�V�F�[�_�I�u�W�F�N�g
std::array<PipelineSet, 6> Model::pip;

void Model::StaticInitialize()
{
	device = DirectX_::GetInstance()->GetDevice();
	cmdList = DirectX_::GetInstance()->GetCommandList();

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateModelPipline(blob, (BlendMode)i, device.Get(), pip);
	}

	filePaths.resize(maxModel);
}

void Model::LoadShader()
{
	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	blob.vs = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicVS.hlsl", "main", "vs_5_0", blob.vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	blob.ps = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicPS.hlsl", "main", "ps_5_0", blob.ps.Get());
}

void Model::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		cmdList->SetPipelineState(pip[0].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		cmdList->SetPipelineState(pip[1].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		cmdList->SetPipelineState(pip[2].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		cmdList->SetPipelineState(pip[3].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		cmdList->SetPipelineState(pip[4].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		cmdList->SetPipelineState(pip[5].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[5].rootSignature.Get());

		break;
	}
}

uint32_t Model::CreateObjModel(const std::string& filePath, bool smoothing)
{
	std::string path = filePath;

	path += smoothing ? " : true" : " : false";

	//���ǂݍ��񂾂��Ƃ�����t�@�C���͂��̂܂ܕԂ�
	auto itr = find_if(modelDatas.begin(), modelDatas.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});

	if (itr == modelDatas.end())
	{
		uint32_t modelHandle = modelCount;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		Obj::Create(filePath.c_str(), smoothing, data.get());

		data->modelHandle = modelCount;

		data->filePath = path;

		modelDatas[path] = std::move(data);

		filePaths[modelCount] = path;

		modelCount++;

		return modelHandle;
	}
	else
	{
		uint32_t modelHandle = modelDatas[path]->modelHandle;

		return modelHandle;
	}
}

void Model::DrawModel(Transform* transform, myMath::Vector4 color)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = modelData->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = modelData->indexBuffer->GetView();

	tmp = color;
	col->Update(&tmp);

	BlendSet(static_cast<BlendMode>(blendMode));

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	cmdList->SetGraphicsRootConstantBufferView(2, col->GetAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^3�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(3, modelData->textureData->gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(modelData->maxIndex, 1, 0, 0, 0);
}

myMath::Matrix4& Model::GetMatWorld()
{
	return modelData->matWorld;
}

const std::vector<PosNormalUv> Model::GetVertices()
{
	return modelData->vertices;
}

const std::vector<uint32_t> Model::GetIndices()
{
	return modelData->indices;
}

void Model::SetModel(uint32_t modelHandle)
{
	modelData = modelDatas[filePaths[modelHandle]].get();
}

void Model::SetModelBlendMode(BlendMode mode)
{
	blendMode = int(mode);
}

Model::Model()
{
	col = std::make_unique<ConstantBuffer>();
	col->Create(sizeof(myMath::Vector4));
}