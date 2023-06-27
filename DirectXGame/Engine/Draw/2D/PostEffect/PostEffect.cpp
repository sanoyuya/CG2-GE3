#include "PostEffect.h"
#include <d3dx12.h>

const float PostEffect::sClearColor_[4] = { 0.25f,0.5f,0.1f,0.0f };//緑っぽい色
std::array <Blob, 8> PostEffect::sBlob_;//シェーダオブジェクト
std::array <PipelineSet, 8> PostEffect::sPip_;
EffectMode PostEffect::sEffectMode_ = EffectMode::None;//何も掛けない状態で初期化
float PostEffect::power_ = 0.0f;

void PostEffect::Initialize(WindowsApp* windowsApp)
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

void PostEffect::Draw()
{
	constBuffMap_ = power_;
	constBuffMaterial_->Update(&constBuffMap_);

	//パイプラインステートとルートシグネチャの設定コマンド
	SetPipline();

	//描画コマンド
	DrawCommand();
}

void PostEffect::VertSetting()
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

void PostEffect::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(VertexPosUV));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void PostEffect::CreateTexBuff(WindowsApp* windowsApp)
{
	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

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
		IID_PPV_ARGS(&texBuff_));
	assert(SUCCEEDED(result));
#else
	DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&clearValue,
		IID_PPV_ARGS(&texBuff_));
#endif // _DEBUG
}

void PostEffect::PreDrawScene(WindowsApp* windowsApp)
{
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
	//リソースバリアを変更(シェーダーリソース->描画可能)
	DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &transition);

	//レンダーターゲットビュー用デスクリプタヒープのハンドル取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH = descHeapRTV_->GetCPUDescriptorHandleForHeapStart();

	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV_->GetCPUDescriptorHandleForHeapStart();

	//レンダーターゲットをセット
	DirectXBase::GetInstance()->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//ビューポートの設定
	auto viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, windowsApp->GetWidth(), windowsApp->GetHeight());
	DirectXBase::GetInstance()->GetCommandList()->RSSetViewports(1, &viewPort);

	//シザリング矩形の設定
	auto rect = CD3DX12_RECT(0, 0, static_cast<LONG>(windowsApp->GetWidth()), static_cast<LONG>(windowsApp->GetHeight()));
	DirectXBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &rect);

	//全画面クリア
	DirectXBase::GetInstance()->GetCommandList()->ClearRenderTargetView(rtvH, sClearColor_, 0, nullptr);
	//深度バッファのクリア
	DirectXBase::GetInstance()->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::PostDrawScene()
{
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrier);
}

void PostEffect::SetEffectMode(const EffectMode& mode)
{
	if (sEffectMode_ != mode)
	{
		sEffectMode_ = mode;
	}
}

void PostEffect::SetPower(const float power)
{
	if (power_ != power)
	{
		power_ = power;
	}
}

void PostEffect::CreateRTV()
{
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
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

	//デスクリプタヒープにRTV作成
	DirectXBase::GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_.Get(), &renderTargetViewDesc, descHeapRTV_->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::CreateDepth(WindowsApp* windowsApp)
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
#endif // DEBUG
}

void PostEffect::CreateDSV()
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

void PostEffect::CreatePipline()
{
	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreatePostEffectPipline(sBlob_[i], sPip_[i]);
	}
}

void PostEffect::LoadShader()
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
}

void PostEffect::DrawCommand()
{
	// プリミティブ形状の設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	auto vbView = vertexBuffer_->GetView();
	// 頂点バッファビューの設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial_.get()->GetAddress());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = handle_.gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	auto ibView = indexBuffer_->GetView();
	//インデックスバッファビューの設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->IASetIndexBuffer(&ibView);

	// 描画コマンド
	DirectXBase::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void PostEffect::CreateSRV()
{
	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープを加算
	handle_ = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(), &srvDesc, handle_.cpuHandle);
}

void PostEffect::SetPipline()
{
	switch (sEffectMode_)
	{
	case None:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[0].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());
		break;
	case BrightnessUP:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[1].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[1].rootSignature.Get());
		break;
	case Inverse:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[2].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[2].rootSignature.Get());
		break;
	case Blur:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[3].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[3].rootSignature.Get());
		break;
	case GaussianBlur:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[4].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[4].rootSignature.Get());
		break;
	case GrayScale:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[5].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[5].rootSignature.Get());
		break;
	case SepiaColor:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[6].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[6].rootSignature.Get());
		break;
	case UVShift:
		DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[7].pipelineState.Get());
		DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[7].rootSignature.Get());
		break;
	}
}