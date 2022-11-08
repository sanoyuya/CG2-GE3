#pragma once
#include"DirectX_.h"

struct TextureData
{
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff;

	//デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvHeap;

	//GPUデスクリプタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	char PADING[4];
	//横幅
	size_t width = 0;
	//縦幅
	size_t height = 0;
};

class TextureManager
{
public:
	//エイリアステンプレート
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	ComPtr<ID3D12Device> device = 0;
	ComPtr<ID3D12DescriptorHeap> dsvHeap=0;
	D3D12_DESCRIPTOR_RANGE dsvRange = {};
	D3D12_HEAP_PROPERTIES prop = {};

	UINT texCount = 0;

	static TextureManager* textureManager;

public:
	void Initialize();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	TextureData LoadTexture(const std::string& filePath);

	/// <summary>
	/// インスタンスを解放
	/// </summary>
	void Destroy();

	static TextureManager* GetInstance();

private:

	TextureManager() = default;
	~TextureManager() = default;

	//コピーコンストラクタ・代入演算子削除
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&) = delete;
};