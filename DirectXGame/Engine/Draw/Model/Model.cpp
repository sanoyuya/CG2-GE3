#include "Model.h"
#include"DirectXBase.h"
#include"Obj.h"

Microsoft::WRL::ComPtr<ID3D12Device> Model::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Model::cmdList;
std::vector<std::string>Model::filePaths;
std::unordered_map<std::string, std::unique_ptr<ModelData>> Model::modelDatas;
uint32_t Model::modelCount;
std::array <Blob, 3> Model::blob;//シェーダオブジェクト
std::array <std::array<PipelineSet, 6>, 3> Model::pip;

void Model::StaticInitialize()
{
	device = DirectXBase::GetInstance()->GetDevice();
	cmdList = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateBasicModelPipline(blob[0], (BlendMode)i, device.Get(), pip[0]);//Basicシェーダー用
		Pipeline::CreateBasicModelPipline(blob[1], (BlendMode)i, device.Get(), pip[1]);//Phongシェーダー用
	}

	filePaths.resize(maxModel);
}

void Model::LoadShader()
{
#pragma region Basicシェーダー用

	//頂点シェーダの読み込みとコンパイル
	blob[0].vs = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicVS.hlsl", "main", "vs_5_0", blob[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	blob[0].ps = DrawCommon::ShaderCompile(L"Resources/shaders/ModelBasicPS.hlsl", "main", "ps_5_0", blob[0].ps.Get());

#pragma endregion Basicシェーダー用

#pragma region Phongシェーダー用

	//頂点シェーダの読み込みとコンパイル
	blob[1].vs = DrawCommon::ShaderCompile(L"Resources/shaders/PhoneVS.hlsl", "main", "vs_5_0", blob[1].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	blob[1].ps = DrawCommon::ShaderCompile(L"Resources/shaders/PhonePS.hlsl", "main", "ps_5_0", blob[1].ps.Get());

#pragma endregion Phongシェーダー用
}

void Model::PiplineSet(BlendMode bMode,ShaderMode sMode)
{
	switch (bMode)
	{
	case BlendMode::None:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][0].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][0].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][0].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][0].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;

	case BlendMode::Alpha:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][1].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][1].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][1].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][1].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;

	case BlendMode::Add:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][2].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][2].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][2].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][2].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;

	case BlendMode::Sub:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][3].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][3].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][3].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][3].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;

	case BlendMode::Mul:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][4].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][4].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][4].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][4].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;

	case BlendMode::Inv:

		switch (sMode)
		{
		case ShaderMode::Basic:

			cmdList->SetPipelineState(pip[0][5].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[0][5].rootSignature.Get());

			break;
		case ShaderMode::Phong:

			cmdList->SetPipelineState(pip[1][5].pipelineState.Get());
			cmdList->SetGraphicsRootSignature(pip[1][5].rootSignature.Get());

			break;
		case ShaderMode::Lambert:
			break;
		}

		break;
	}
}

uint32_t Model::CreateObjModel(const std::string& filePath, bool smoothing)
{
	std::string path = filePath;

	path += smoothing ? " : true" : " : false";

	//一回読み込んだことがあるファイルはそのまま返す
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

	PiplineSet(static_cast<BlendMode>(blendMode),static_cast<ShaderMode>(shaderMode));

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	cmdList->SetGraphicsRootConstantBufferView(2, col->GetAddress());

	//ライトの描画
	if (shaderMode != ShaderMode::Basic)
	{

	}

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRVヒープの先頭にあるSRVをルートパラメータ3番に設定
	cmdList->SetGraphicsRootDescriptorTable(3, modelData->textureData->gpuHandle);

	// 描画コマンド
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
	blendMode = mode;
}

void Model::SetShaderMode(ShaderMode mode)
{
	shaderMode = mode;
}

Model::Model()
{
	col = std::make_unique<ConstantBuffer>();
	col->Create(sizeof(myMath::Vector4));
}