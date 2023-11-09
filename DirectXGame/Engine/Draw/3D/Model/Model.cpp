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
std::array <Blob, 6> Model::sBlob_;//シェーダオブジェクト
std::array <std::array<PipelineSet, 6>, 6> Model::sPip_;
ShaderMode Model::sShaderMode_ = ShaderMode::Basic;//標準

void Model::StaticInitialize()
{
	sDevice_ = DirectXBase::GetInstance()->GetDevice();
	sCmdList_ = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateBasicModelPipline(sBlob_[0], (BlendMode)i, sDevice_.Get(), sPip_[0]);//Basicシェーダー用
		Pipeline::CreatePhongModelPipline(sBlob_[1], (BlendMode)i, sDevice_.Get(), sPip_[1]);//Phongシェーダー用
		Pipeline::CreatePhongModelPipline(sBlob_[2], (BlendMode)i, sDevice_.Get(), sPip_[2]);//Toonシェーダー用
		Pipeline::CreatePhongModelPipline(sBlob_[3], (BlendMode)i, sDevice_.Get(), sPip_[3]);//リムライト用
		Pipeline::CreateMultiPhongModelPipline(sBlob_[4], (BlendMode)i, sDevice_.Get(), sPip_[4]);//マルチレンダーターゲット用
		Pipeline::CreateBasicModelPipline(sBlob_[5], (BlendMode)i, sDevice_.Get(), sPip_[5]);//単色シェーダー用
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
#pragma region Basicシェーダー用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[0].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Basic/ModelBasicVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[0].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Basic/ModelBasicPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());

#pragma endregion Basicシェーダー用

#pragma region Phongシェーダー用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[1].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Phong/PhongVS.hlsl", "main", "vs_5_0", sBlob_[1].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[1].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Phong/PhongPS.hlsl", "main", "ps_5_0", sBlob_[1].ps.Get());

#pragma endregion Phongシェーダー用

#pragma region Toonシェーダー用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[2].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Toon/ToonVS.hlsl", "main", "vs_5_0", sBlob_[2].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[2].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Toon/ToonPS.hlsl", "main", "ps_5_0", sBlob_[2].ps.Get());

#pragma endregion Toonシェーダー用

#pragma region リムライト用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[3].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/RimLight/RimLightVS.hlsl", "main", "vs_5_0", sBlob_[3].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[3].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/RimLight/RimLightPS.hlsl", "main", "ps_5_0", sBlob_[3].ps.Get());

#pragma endregion リムライト用

#pragma region マルチレンダーターゲット用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[4].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Phong/PhongVS.hlsl", "main", "vs_5_0", sBlob_[4].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[4].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Phong/MultiPhongPS.hlsl", "main", "ps_5_0", sBlob_[4].ps.Get());

#pragma endregion マルチレンダーターゲット用

#pragma region Basicシェーダー用

	//頂点シェーダの読み込みとコンパイル
	sBlob_[5].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Basic/ModelBasicVS.hlsl", "main", "vs_5_0", sBlob_[5].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[5].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Model/Basic/SimpleColorPS.hlsl", "main", "ps_5_0", sBlob_[5].ps.Get());

#pragma endregion Basicシェーダー用
}

void Model::PiplineSet(BlendMode bMode, ShaderMode sMode)
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][0].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][0].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][0].rootSignature.Get());
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][1].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][1].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][1].rootSignature.Get());
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][2].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][2].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][2].rootSignature.Get());
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][3].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][3].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][3].rootSignature.Get());
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][4].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][4].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][4].rootSignature.Get());
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
		case ShaderMode::MultiPhong:
			sCmdList_->SetPipelineState(sPip_[4][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[4][5].rootSignature.Get());
			break;
		case ShaderMode::SimpleColor:
			sCmdList_->SetPipelineState(sPip_[5][5].pipelineState.Get());
			sCmdList_->SetGraphicsRootSignature(sPip_[5][5].rootSignature.Get());
			break;
		}

		break;
	}
}

uint32_t Model::CreateObjModel(const std::string& filePath, bool smoothing, bool flipX, bool flipY, bool flipZ)
{
	std::string path = filePath;

	path += smoothing ? " : true" : " : false";

	//一回読み込んだことがあるファイルはそのまま返す
	auto itr = find_if(sModelDatas_.begin(), sModelDatas_.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});

	if (itr == sModelDatas_.end())
	{
		uint32_t modelHandle = sModelCount_;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		Obj::Create(filePath.c_str(), smoothing, data.get(), flipX, flipY, flipZ);

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

uint32_t Model::CreateAssimpModel(const std::string& filePath)
{
	std::string path = filePath;

	//一回読み込んだことがあるファイルはそのまま返す
	auto itr = find_if(sModelDatas_.begin(), sModelDatas_.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});

	if (itr == sModelDatas_.end())
	{
		uint32_t modelHandle = sModelCount_;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		std::vector<Mesh> sMeshes_;//メッシュの配列
		ImportSettings sSet_ = { nullptr,sMeshes_,false,false };

		wchar_t wfilepath[256];

		MultiByteToWideChar(CP_ACP, 0, filePath.c_str(), -1, wfilepath, _countof(wfilepath));
		sSet_.filename = wfilepath;
		sSet_.inverseU = false;
		sSet_.inverseV = true;
		sSet_.meshes = sMeshes_;

		AssimpLoder::Load(sSet_, data.get());

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

void Model::DrawModel(Transform* transform, myMath::Vector4 color, myMath::Vector2 tiling)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = modelData_->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = modelData_->indexBuffer->GetView();

	tmp_.color = color;
	tmp_.tiling = tiling;
	constantBuff_->Update(&tmp_);

	PiplineSet(static_cast<BlendMode>(blendMode_), static_cast<ShaderMode>(shaderMode_));

	// プリミティブ形状の設定コマンド
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	sCmdList_->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	sCmdList_->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	sCmdList_->SetGraphicsRootConstantBufferView(1, modelData_->constBuffMaterial->GetAddress());
	//ルートパラメータ2番に色情報を設定
	sCmdList_->SetGraphicsRootConstantBufferView(2, constantBuff_->GetAddress());

	//ライトの描画
	if (shaderMode_ != ShaderMode::Basic && shaderMode_ != ShaderMode::SimpleColor)
	{
		//ルートパラメータ2番にライト情報を設定
		sLightManager_->Draw(sCmdList_.Get(), 4);
	}

	// SRVヒープの設定コマンド
	sCmdList_->SetDescriptorHeaps(1, modelData_->textureData->srvHeap.GetAddressOf());

	// SRVヒープの先頭にあるSRVをルートパラメータ3番に設定
	sCmdList_->SetGraphicsRootDescriptorTable(3, modelData_->textureData->gpuHandle);

	// 描画コマンド
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

void Model::SetModel(const uint32_t modelHandle)
{
	modelData_ = sModelDatas_[sFilePaths_[modelHandle]].get();
}

void Model::SetModelBlendMode(const BlendMode& mode)
{
	if (blendMode_ != mode)
	{
		blendMode_ = mode;
	}
}

void Model::SetShaderMode(const ShaderMode& mode)
{
	if (shaderMode_ != mode)
	{
		shaderMode_ = mode;
	}
}

void Model::SetStaticShaderMode(const ShaderMode& mode)
{
	if (sShaderMode_ != mode)
	{
		sShaderMode_ = mode;
	}
}

Model::Model()
{
	constantBuff_ = std::make_unique<ConstantBuffer>();
	constantBuff_->Create(sizeof(TilingColor));
}

Model::~Model()
{
}