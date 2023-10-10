#pragma once
#include<wrl.h>
#include <d3d12.h>
#include <cstdint>

/// <summary>
/// インデックスバッファ
/// </summary>
class IndexBuffer
{
private:

	//インデックスバッファ生成が成功したか
	bool isValid_ = false;
	char PADING_[7];

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer_;

	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW bufferView_{};

	void* bufferMappedPtr_ = nullptr;

	size_t bufferLength_ = 0;

public:

	/// <summary>
	/// インデックスバッファを生成
	/// </summary>
	/// <param name="length">インデックスバッファの要素数</param>
	/// <param name="data">インデックス配列の先頭アドレス(uint32_t)</param>
	void Create(size_t length, const uint32_t* data = nullptr);

	/// <summary>
	/// 成功したか
	/// </summary>
	bool IsValid();

	/// <summary>
	/// インデックスバッファビューを取得
	/// </summary>
	D3D12_INDEX_BUFFER_VIEW GetView() const;

	/// <summary>
	/// データの更新
	/// </summary>
	/// <param name="data">データ</param>
	void Update(void* data);

	IndexBuffer() = default;
	~IndexBuffer() = default;

private:

	IndexBuffer(const IndexBuffer&) = delete;
	void operator = (const IndexBuffer&) = delete;
};