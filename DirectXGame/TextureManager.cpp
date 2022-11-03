#include "TextureManager.h"
#include"DirectXTex.h"

TextureManager* TextureManager::textureManager = nullptr;

void TextureManager::Initialize()
{
	HRESULT result;
	device = DirectX_::GetInstance()->GetDevice();
	size_t maxCount = 1024;

	//デスクリプタレンジの設定
	dsvRange.NumDescriptors = 1;//一度の描画に使うテクスチャの数
	dsvRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	dsvRange.BaseShaderRegister = 0;//レジスタ番号
	dsvRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NumDescriptors = (UINT)maxCount;

	//デスクリプタヒープの生成
	result = device->CreateDescriptorHeap(&srvDesc, IID_PPV_ARGS(dsvHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//ヒープ設定
	prop.Type = D3D12_HEAP_TYPE_CUSTOM;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
}

TextureData TextureManager::LoadTexture(const std::string& filePath)
{
	wchar_t wfilePath[256];
	HRESULT result;

	if (texCount > 1024)
	{
		assert(0);
	}

	TextureData tmp{};

	DirectX::TexMetadata metaData{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	MultiByteToWideChar(CP_ACP, 0, filePath.c_str(), -1, wfilePath, _countof(wfilePath));

	//WICテクスチャのロード
	result = DirectX::LoadFromWICFile(
		wfilePath,
		DirectX::WIC_FLAGS_NONE,
		&metaData, scratchImg);
	assert(SUCCEEDED(result));

	//ミップマップ生成
	result = DirectX::GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metaData = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metaData.format = DirectX::MakeSRGB(metaData.format);

	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metaData.format;
	textureResourceDesc.Width = metaData.width;//幅
	textureResourceDesc.Height = (UINT)metaData.height;
	textureResourceDesc.DepthOrArraySize = (UINT16)metaData.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//テクスチャバッファの生成
	result = device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(tmp.texBuff.ReleaseAndGetAddressOf()));

	//テクスチャバッファにデータ転送
	for (size_t i = 0; i < metaData.mipLevels; i++)
	{
		//ミップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		//テクスチャバッファにデータ転送
		result = tmp.texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,//全領域へコピー
			img->pixels,//元データアドレス
			(UINT)img->rowPitch,//1ラインサイズ
			(UINT)img->slicePitch);//1枚サイズ
	}
	assert(SUCCEEDED(result));

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	tmp.gpuHandle = dsvHeap->GetGPUDescriptorHandleForHeapStart();
	tmp.srvHeap = dsvHeap;

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64>(texCount) * incrementSize;
	tmp.gpuHandle.ptr += static_cast<UINT64>(texCount) * incrementSize;

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metaData.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metaData.mipLevels);

	//ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateShaderResourceView(tmp.texBuff.Get(), &srvDesc, cpuHandle);

	tmp.width = metaData.width;
	tmp.height = metaData.height;

	texCount++;

	return tmp;
}

void TextureManager::Destroy()
{
	delete textureManager;
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}