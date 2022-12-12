#pragma once
#include"DirectX_.h"
#include <memory>
#include<DirectXTex.h>

struct TextureData
{
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	//デスクプリタヒープ
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;

	//GPUデスクプリタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//横幅
	size_t width = 0;
	//縦幅
	size_t height = 0;

	//カラー
	myMath::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };

	std::string path;

	uint32_t textureHandle;

private:
	char PADING[4]{};
};

class TextureManager
{
private:

	DirectX_* directX_;

	static TextureManager* textureManager;

	//テクスチャ数
	uint32_t nextTexture;

	// ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<TextureData>> textureDatas;

public:

	/// <summary>
	/// テクスチャをロードします
	/// </summary>
	/// <param name="filepath">テクスチャのファイルパス</param>
	/// <returns>テクスチャハンドル</returns>
	uint32_t LoadTexture(const std::string& path);

	/// <summary>
	/// 初期化
	/// </summary>
	void StaticInitialize();

	/// <summary>
	/// インスタンスを所得
	/// </summary>
	/// <returns>インスタンス</returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// インスタンスを解放
	/// </summary>
	void Destroy();

	/// <summary>
	/// テクスチャをロードします
	/// </summary>
	/// <param name="filepath">テクスチャのファイルパス</param>
	/// <returns>テクスチャハンドル</returns>
	static uint32_t Load(const std::string& path);

	static TextureData* GetTextureData(uint32_t handle);

private:

	TextureManager() = default;
	~TextureManager() = default;

	Microsoft::WRL::ComPtr<ID3D12Resource>CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	D3D12_GPU_DESCRIPTOR_HANDLE CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata);

	void LoadFile(const std::string& path, DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	TextureData* FromTextureData(const std::string& path);
};