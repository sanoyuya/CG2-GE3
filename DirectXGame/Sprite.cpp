#include "Sprite.h"
#include <d3dcompiler.h>
#include"Camera.h"

Microsoft::WRL::ComPtr<ID3D12Device>Sprite::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>Sprite::cmdList;
myMath::Matrix4 Sprite::matProjection;
Blob Sprite::blob;//シェーダオブジェクト
std::array<PipelineSet, 6> Sprite::pip;

void Sprite::Initialize()
{
	device = DirectX_::GetInstance()->GetDevice();
	cmdList = DirectX_::GetInstance()->GetCommandList();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetHeight());

	myMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateSpritePipline(blob, (BlendMode)i, device.Get(), pip);
	}
}

void Sprite::SpriteInitialize()
{
	CreateVertexIndexBuffer();

	CreateConstBuff();
}

void Sprite::DrawSprite(TextureData& textureData, myMath::Vector2 position, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height) * isFlipY;

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{0.0f,1.0f},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{1.0f,0.0f},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{1.0f,1.0f},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint16_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//インデックスをコピー
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//インデックスをコピー
	}

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	BlendSet((BlendMode)blendMode);

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteX(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width/ sheetsNum) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width / sheetsNum) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height) * isFlipY;

	if (nowNum + 1 > sheetsNum)
	{
		nowNum = 0;//0枚目に戻す処理
	}

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(float)nowNum / (float)sheetsNum,0.0f},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{(float)nowNum / (float)sheetsNum,1.0f},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{((float)nowNum + 1) / (float)sheetsNum,0.0f},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{((float)nowNum + 1) / (float)sheetsNum,1.0f},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint16_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//インデックスをコピー
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//インデックスをコピー
	}

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	BlendSet((BlendMode)blendMode);

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteY(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height/ sheetsNum) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height / sheetsNum) * isFlipY;

	if (nowNum + 1 > sheetsNum)
	{
		nowNum = 0;//0枚目に戻す処理
	}

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,(float)nowNum / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{0.0f,((float)nowNum + 1) / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{1.0f,(float)nowNum / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{1.0f,((float)nowNum + 1) / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint16_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//インデックスをコピー
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//インデックスをコピー
	}

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	BlendSet((BlendMode)blendMode);

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteXY(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width/ sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height/ sheetsNumY) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height / sheetsNumY) * isFlipY;

	uint16_t animationXYNum = sheetsNumX * sheetsNumY;//分割数(総合計)
	uint16_t x = nowNum % sheetsNumX;
	uint16_t y = nowNum / sheetsNumX;

	if (nowNum + 1 > animationXYNum)
	{
		nowNum = 0;//0枚目に戻す処理
	}

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(float)x / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{(float)x / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{((float)x + 1) / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{((float)x + 1) / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint16_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//インデックスをコピー
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//インデックスをコピー
	}

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	BlendSet((BlendMode)blendMode);

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::SetBlendMode(BlendMode mode)
{
	blendMode = int(mode);
}

void Sprite::CreateVertexIndexBuffer()
{
	//ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};

	//頂点データ全体のサイズ = 頂点データサイズ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * 4);

	//頂点バッファの設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//頂点バッファの生成
	result = device->CreateCommittedResource(
		&heapProp,//リソース設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//頂点バッファビューの作成
	//GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(PosUvColor);

	//インデックスデータのサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * 6);
	//頂点バッファの設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定　
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//インデックスバッファの生成
	result = device->CreateCommittedResource(
		&heapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(indexBuff.ReleaseAndGetAddressOf()));

	//インデックスバッファのマッピング
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//マッピング解除
	indexBuff->Unmap(0, nullptr);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	assert(SUCCEEDED(result));
}

void Sprite::CreateConstBuff()
{
	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(myMath::Matrix4) + 0xff) & ~0xff;//頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//定数バッファのマッピング
	result = constBuff->Map(0, nullptr, (void**)&constBuffMap);//マッピング
	assert(SUCCEEDED(result));
}

void Sprite::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	blob.vs = DrawCommon::ShaderCompile(L"Resources/shaders/SpriteVS.hlsl", "main", "vs_5_0", blob.vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	blob.ps = DrawCommon::ShaderCompile(L"Resources/shaders/SpritePS.hlsl", "main", "ps_5_0", blob.ps.Get());
}

void Sprite::Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation)
{
	myMath::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation({ position.x,position.y,0.0f });
	//回転行列
	mRot.MakeRotation({ 0.0f,0.0f,rotation });
	//スケール行列
	mScale.MakeScaling({ scale.x,scale.y,1.0f });
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	*constBuffMap = matWorld * matProjection;
}

void Sprite::BlendSet(BlendMode mode)
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