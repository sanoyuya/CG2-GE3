#include "MultiLenderPostEffect.h"
#include <d3dx12.h>
#include"InputManager.h"

const float MultiLenderPostEffect::sClearColor_[4] = { 0.25f,0.5f,0.1f,0.0f };//緑っぽい色
myMath::Matrix4 MultiLenderPostEffect::matProjection_;
std::array <Blob, 5> MultiLenderPostEffect::sBlob_;//シェーダオブジェクト
std::array <PipelineSet, 5> MultiLenderPostEffect::sPip_;

void MultiLenderPostEffect::Initialize(WindowsApp* windowsApp)
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

void MultiLenderPostEffect::Draw()
{
	if (InputManager::GetInstance()->KeyboardTriggerPush(DIK_0))
	{
		//デスクリプタヒープにSRV作成
		static int8_t tex = 0;
		//テクスチャ番号を0と1で切り替え
		tex = (tex + 1) % 2;

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_[tex].Get(),
			&srvDesc, DirectXBase::GetInstance()->GetDescriptorHeap()->GetHeap()->GetCPUDescriptorHandleForHeapStart());
	}
	matProjection_ = myMath::MakeIdentity();
	constBuffMap_ = matProjection_;
	constBuffMaterial_->Update(&constBuffMap_);

	// パイプラインステートとルートシグネチャの設定コマンド
	DirectXBase::GetInstance()->GetCommandList()->SetPipelineState(sPip_[0].pipelineState.Get());
	DirectXBase::GetInstance()->GetCommandList()->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());

	//描画コマンド
	DrawCommand();
}

void MultiLenderPostEffect::VertSetting()
{
	//頂点データ
	PosUvColor vertices[] =
	{
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{-1.0f,1.0f,0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{1.0f,-1.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{1.0f,1.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
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

void MultiLenderPostEffect::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(PosUvColor));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void MultiLenderPostEffect::CreateTexBuff(WindowsApp* windowsApp)
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
		HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&clearValue,
			IID_PPV_ARGS(&texBuff_[i]));
		assert(SUCCEEDED(result));
	}
}

void MultiLenderPostEffect::PreDrawScene(WindowsApp* windowsApp)
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

void MultiLenderPostEffect::PostDrawScene()
{
	for (int8_t i = 0; i < 2; i++)
	{
		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff_[i].Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		DirectXBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrier);
	}
}

void MultiLenderPostEffect::CreateRTV()
{
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 2;
	//RTV用デスクリプタヒープを作成
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));

	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//シェーダーの計算結果をSRGBに変換して書き込む
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	for (int8_t i = 0; i < 2; i++)
	{
		//デスクリプタヒープにRTV作成
		//DirectXBase::GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_[i].Get(), &renderTargetViewDesc, descHeapRTV_->GetCPUDescriptorHandleForHeapStart());
		DirectXBase::GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_[i].Get(),
			&renderTargetViewDesc, CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeapRTV_->GetCPUDescriptorHandleForHeapStart(),
				i, DirectXBase::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
	}
}

void MultiLenderPostEffect::CreateDepth(WindowsApp* windowsApp)
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
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&properties,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&depthBuff_));
	assert(SUCCEEDED(result));
}

void MultiLenderPostEffect::CreateDSV()
{
	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvDescHeapDesc{};
	dsvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvDescHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを作成
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateDescriptorHeap(&dsvDescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
	assert(SUCCEEDED(result));

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DirectXBase::GetInstance()->GetDevice()->CreateDepthStencilView(depthBuff_.Get(), &dsvDesc, descHeapDSV_->GetCPUDescriptorHandleForHeapStart());
}

void MultiLenderPostEffect::CreatePipline()
{
	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreatePostEffectPipline(sBlob_[0], sPip_[0]);
	}
}

void MultiLenderPostEffect::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	sBlob_[0].vs = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectVS.hlsl", "main", "vs_5_0", sBlob_[0].vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_[0].ps = DrawCommon::ShaderCompile(L"Resources/Shaders/PostEffect/PostEffectPS.hlsl", "main", "ps_5_0", sBlob_[0].ps.Get());
}

void MultiLenderPostEffect::DrawCommand()
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

void MultiLenderPostEffect::CreateSRV()
{
	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープを加算
	handle_ = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_[0].Get(), &srvDesc, handle_.cpuHandle);
}