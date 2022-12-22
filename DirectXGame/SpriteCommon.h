#pragma once
#include"DrawCommon.h"
#include"Pipeline.h"
#include"DirectX_.h"
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

	static void Initialize();

	static void BlendSet(BlendMode mode);

	static void DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff);

private:

	static void LoadShader();
};