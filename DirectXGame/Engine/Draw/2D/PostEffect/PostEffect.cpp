#include "PostEffect.h"
#include <d3dx12.h>

void PostEffect::Initialize(WindowsApp* windowsApp)
{
	//テクスチャ読み込み
	tex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	//基底クラスとしての初期化
	Sprite2D::Sprite2DInitialize(tex_);

	CreateTexBuff(windowsApp);

	CreateDescHeap();

	scale_ = { 500.0f,500.0f };
	color_ = { 1.0f,1.0f ,1.0f ,1.0f };
}

void PostEffect::Draw()
{
	int isFlipX, isFlipY;
	if (flipX_ == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY_ == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint_.x) * texture_->width) * isFlipX;
	float right = ((1.0f - anchorpoint_.x) * texture_->width) * isFlipX;
	float top = ((0.0f - anchorpoint_.y) * texture_->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint_.y) * texture_->height) * isFlipY;

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color_.x, color_.y, color_.z, color_.w}},//左上インデックス0
		{{left,bottom,0.0f},{0.0f,1.0f},{color_.x, color_.y, color_.z, color_.w}},//左下インデックス1
		{{right,top,0.0f},{1.0f,0.0f},{color_.x, color_.y, color_.z, color_.w}},//右上インデックス2
		{{right,bottom,0.0f},{1.0f,1.0f},{color_.x, color_.y, color_.z, color_.w}},//右下インデックス3
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

	Update(position_, scale_, rotation_);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void PostEffect::CreateTexBuff(WindowsApp* windowsApp)
{
	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(windowsApp->GetWidth()),
		static_cast<UINT>(windowsApp->GetHeight()),
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	// リソースを生成
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(&texBuff_));
	assert(SUCCEEDED(result));

	//画素数(1280*720=921600ピクセル)
	const uint32_t pixelCount = static_cast<uint32_t>(windowsApp->GetWidth() * windowsApp->GetHeight());
	//画素1行分のデータサイズ
	const uint32_t rowPitch = sizeof(uint32_t) * static_cast<uint32_t>(windowsApp->GetWidth());
	//画像全体のデータサイズ
	const uint32_t depthPitch = rowPitch * static_cast<uint32_t>(windowsApp->GetHeight());
	//画像イメージ
	UINT* img = new UINT[pixelCount];
	for (uint32_t i = 0; i < pixelCount; i++)
	{
		img[i] = 0xff0000ff;
	}

	//テクスチャバッファにデータ転送
	result = texBuff_->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
	assert(SUCCEEDED(result));
	delete[]img;
}

void PostEffect::CreateDescHeap()
{
	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープにSRV作成
	handle_ = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(), &srvDesc, handle_.cpuHandle);
}