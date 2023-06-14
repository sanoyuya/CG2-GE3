#pragma once
#include"DrawCommon.h"
#include"Pipeline.h"
#include"DirectXBase.h"
#include <wrl.h>
#include <d3d12.h>
#include "TextureManager.h"
#include "ConstantBuffer.h"

class SpriteCommon
{
public:

	static Microsoft::WRL::ComPtr<ID3D12Device>device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList;

	static Blob blob;//シェーダオブジェクト

	static std::array<PipelineSet, 6> pip;//パイプライン

public:

	/// <summary>
	/// 静的初期化処理
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// パイプラインに設定を適用
	/// </summary>
	/// <param name="mode"></param>
	static void BlendSet(BlendMode mode);

	/// <summary>
	/// コマンドリスト実行
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	/// <param name="vbView"></param>
	/// <param name="ibView"></param>
	/// <param name="constBuff">定数バッファ</param>
	static void DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff);

private:

	static void LoadShader();
};