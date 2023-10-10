#include "MultiTexturePostEffect.h"
#include <d3dx12.h>
#include"InputManager.h"
#include <algorithm>

const float MultiTexturePostEffect::sClearColor_[4] = { 0.25f,0.5f,0.1f,0.0f };//緑っぽい色
myMath::Matrix4 MultiTexturePostEffect::matProjection_;
std::array <Blob, 11> MultiTexturePostEffect::sBlob_;//シェーダオブジェクト
std::array <PipelineSet, 11> MultiTexturePostEffect::sPip_;
MultiTextureEffectMode MultiTexturePostEffect::sEffectMode_;
PowerGrayScale MultiTexturePostEffect::powerGrayScale_;

void MultiTexturePostEffect::Initialize(WindowsApp* windowsApp)
{
	//バッファの作成
	CreateBuff();

	VertSetting();
	//texBuff_の生成
	CreateTexBuff(windowsApp);
	//SRVの作成
	CreateSRV();
	//RTVの作成
	CreateRTV();
	//深度バッファの生成
	CreateDepth(windowsApp);
	//DSVの作成
	CreateDSV();
	//パイプラインの生成
	CreatePipline();
}

void MultiTexturePostEffect::Draw()
{
	matProjection_ = myMath::MakeIdentity();
	constBuffMap_ = matProjection_;

	constBuffMaterial_->Update(&powerGrayScale_);

	// パイプラインステートとルートシグネチャの設定コマンド
	SetPipline();

	//描画コマンド
	DrawCommand();
}

void MultiTexturePostEffect::VertSetting()
{
	//頂点データ
	VertexPosUV vertices[] =
	{
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f}},//左上インデックス0
		{{-1.0f,1.0f,0.0f},{0.0f,0.0f}},//左下インデックス1
		{{1.0f,-1.0f,0.0f},{1.0f,1.0f}},//右上インデックス2
		{{1.0f,1.0f,0.0f},{1.0f,0.0f}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer_->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer_->Update(indices);
}

void MultiTexturePostEffect::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(VertexPosUV));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void MultiTexturePostEffect::CreateTexBuff(WindowsApp* windowsApp)
{
	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	for (int8_t i = 0; i < 2; i++)
	{
		auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, sClearColor_);
		//テクスチャバッファの生成

#ifdef _DEBUG
		HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&clearValue,
			IID_PPV_ARGS(&texBuff_[i]));
		assert(SUCCEEDED(result));
#else
		DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&clearValue,
			IID_PPV_ARGS(&texBuff_[i]));
#endif // _DEBUG
	}
}

void MultiTexturePostEffect::PreDrawScene(WindowsApp* windowsApp)
{
	for (int8_t i = 0; i < 2; i++)
	{
		auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_[i].Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
		//リソースバリアを変更(シェーダーリソース->描画可能)
		DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &transition);
	}

	//レンダーターゲットビュー用デスクリプタヒープのハンドル取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHs[2];
	for (int8_t i = 0; i < 2; i++)
	{
		rtvHs[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeapRTV_->GetCPUDescriptorHandleForHeapStart(), i,
			DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}

	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV_->GetCPUDescriptorHandleForHeapStart();

	//レンダーターゲットをセット
	DirectXBase::GetInstance()->GetCommandList()->OMSetRenderTargets(2, rtvHs, false, &dsvH);

	CD3DX12_VIEWPORT viewports[2];
	CD3DX12_RECT scissorRects[2];
	for (int8_t i = 0; i < 2; i++)
	{
		viewports[i] = CD3DX12_VIEWPORT(0.0f, 0.0f, windowsApp->GetWidth(), windowsApp->GetHeight());
		scissorRects[i] = CD3DX12_RECT(0, 0, static_cast<LONG>(windowsApp->GetWidth()), static_cast<LONG>(windowsApp->GetHeight()));
	}

	//ビューポートの設定
	DirectXBase::GetInstance()->GetCommandList()->RSSetViewports(2, viewports);

	//シザリング矩形の設定
	DirectXBase::GetInstance()->GetCommandList()->RSSetScissorRects(2, scissorRects);

	for (int8_t i = 0; i < 2; i++)
	{
		//全画面クリア
		DirectXBase::GetInstance()->GetCommandList()->ClearRenderTargetView(rtvHs[i], sClearColor_, 0, nullptr);
	}
	//深度バッファのクリア
	DirectXBase::GetInstance()->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void MultiTexturePostEffect::PostDrawScene()
{
	for (int8_t i = 0; i < 2; i++)
	{
		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_[i].Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrier);
	}
}

void MultiTexturePostEffect::SetEffectMode(const MultiTextureEffectMode& mode)
{
	sEffectMode_ = mode;
}

void MultiTexturePostEffect::SetPower(const float power)
{
	if (powerGrayScale_.power != power)
	{
		powerGrayScale_.power = power;
	}
}

void MultiTexturePostEffect::SetGrayScale(const float grayScale)
{
	if (powerGrayScale_.grayScale != grayScale)
	{
		powerGrayScale_.grayScale = std::clamp(grayScale, 0.0f, 1.0f);
	}
}

void MultiTexturePostEffect::CreateRTV()
{
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 2;
	//RTV用デスクリプタヒープを作成
#ifdef _DEBUG
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));
#else
	DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
#endif // _DEBUG

	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//シェーダーの計算結果をSRGBに変換して書き込む
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	for (int8_t i = 0; i < 2; i++)
	{
		//デスクリプタヒープにRTV作成
		DirectXBase::GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_[i].Get(),
			nullptr, CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeapRTV_->GetCPUDescriptorHandleForHeapStart(),
				i, DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
	}
}

void MultiTexturePostEffect::CreateDepth(WindowsApp* windowsApp)
{
	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	//深度バッファ生成
	auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	auto properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

#ifdef _DEBUG
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&properties,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&depthBuff_));
	assert(SUCCEEDED(result));
#else
	DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&properties,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&depthBuff_));
#endif // _DEBUG
}

void MultiTexturePostEffect::CreateDSV()
{
	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvDescHeapDesc{};
	dsvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvDescHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを作成
#ifdef _DEBUG
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&dsvDescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
	assert(SUCCEEDED(result));
#else
	DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&dsvDescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
#endif // _DEBUG

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DirectXBase::GetInstance()->GetDevice()->CreateDepthStencilView(depthBuff_.Get(), &dsvDesc, descHeapDSV_->GetCPUDescriptorHandleForHeapStart());
}

void MultiTexturePostEffect::CreatePipline()
{
	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateMultiTexturePipline(sBlob_[i], sPip_[i]);
	}
}

void MultiTexturePostEffect::LoadShader()
{
#pragma region None
	//頂点シェーダの読み込みとコンパイル
	sBlob_[0].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[0].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());
#pragma endregion None

#pragma region BrightnessUP
	//頂点シェーダの読み込みとコンパイル
	sBlob_[1].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[1].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[1].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/BrightnessPS.hlsl", "main", "ps_5_0", sBlob_[1].ps.Get());
#pragma endregion BrightnessUP

#pragma region Inverse
	//頂点シェーダの読み込みとコンパイル
	sBlob_[2].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[2].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[2].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/InversePS.hlsl", "main", "ps_5_0", sBlob_[2].ps.Get());
#pragma endregion Inverse

#pragma region Blur
	//頂点シェーダの読み込みとコンパイル
	sBlob_[3].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[3].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[3].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/BlurPS.hlsl", "main", "ps_5_0", sBlob_[3].ps.Get());
#pragma endregion Blur

#pragma region GaussianBlur
	//頂点シェーダの読み込みとコンパイル
	sBlob_[4].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[4].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[4].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/GaussianBlurPS.hlsl", "main", "ps_5_0", sBlob_[4].ps.Get());
#pragma endregion GaussianBlur

#pragma region GrayScale
	//頂点シェーダの読み込みとコンパイル
	sBlob_[5].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[5].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[5].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/GrayScalePS.hlsl", "main", "ps_5_0", sBlob_[5].ps.Get());
#pragma endregion GrayScale

#pragma region SepiaColor
	//頂点シェーダの読み込みとコンパイル
	sBlob_[6].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[6].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[6].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/SepiaColorPS.hlsl", "main", "ps_5_0", sBlob_[6].ps.Get());
#pragma endregion SepiaColor

#pragma region UVShift
	//頂点シェーダの読み込みとコンパイル
	sBlob_[7].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[7].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[7].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/UVShiftPS.hlsl", "main", "ps_5_0", sBlob_[7].ps.Get());
#pragma endregion UVShift

#pragma region Bloom
	//頂点シェーダの読み込みとコンパイル
	sBlob_[8].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[8].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[8].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/BloomPS.hlsl", "main", "ps_5_0", sBlob_[8].ps.Get());
#pragma endregion Bloom

#pragma region マルチテクスチャ
	//頂点シェーダの読み込みとコンパイル
	sBlob_[9].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[9].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/MultiTexturePostEffectPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());
#pragma endregion マルチテクスチャ

#pragma region 高輝度抽出
	//頂点シェーダの読み込みとコンパイル
	sBlob_[10].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[10].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/HighLumiPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());
#pragma endregion 高輝度抽出
}

void MultiTexturePostEffect::DrawCommand()
{
	// プリミティブ形状の設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	auto vbView = vertexBuffer_->GetView();
	//頂点バッファビューの設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial_.get()->GetAddress());

	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(handle_[0].gpuHandle, 0,
			DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
	//SRVヒープ先頭にあるSRVをルートパラメーター2番に設定
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(2,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(handle_[1].gpuHandle, 0,
			DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	auto ibView = indexBuffer_->GetView();
	//インデックスバッファビューの設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetIndexBuffer(&ibView);
	// 描画コマンド
	DirectXBase::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void MultiTexturePostEffect::CreateSRV()
{
	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 2;

	//デスクリプタヒープを加算
	handle_[0] = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	handle_[1] = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	for (int8_t i = 0; i < 2; i++)
	{
		DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_[i].Get(), &srvDesc,
			CD3DX12_CPU_DESCRIPTOR_HANDLE(handle_[i].cpuHandle, 0,
				DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
	}
}

void MultiTexturePostEffect::SetPipline()
{
	switch (sEffectMode_)
	{
	case MultiTextureEffectMode::None:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[0].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());
		break;
	case MultiTextureEffectMode::BrightnessUP:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[1].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[1].rootSignature.Get());
		break;
	case MultiTextureEffectMode::Inverse:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[2].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[2].rootSignature.Get());
		break;
	case MultiTextureEffectMode::Blur:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[3].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[3].rootSignature.Get());
		break;
	case MultiTextureEffectMode::GaussianBlur:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[4].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[4].rootSignature.Get());
		break;
	case MultiTextureEffectMode::GrayScale:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[5].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[5].rootSignature.Get());
		break;
	case MultiTextureEffectMode::SepiaColor:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[6].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[6].rootSignature.Get());
		break;
	case MultiTextureEffectMode::UVShift:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[7].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[7].rootSignature.Get());
		break;
	case MultiTextureEffectMode::Bloom:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[8].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[8].rootSignature.Get());
		break;
	case MultiTextureEffectMode::MultiTexture:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[9].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[9].rootSignature.Get());
		break;
	case MultiTextureEffectMode::HighLumi:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[10].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[10].rootSignature.Get());
		break;
	default:
		break;
	}
}
