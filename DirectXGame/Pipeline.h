#pragma once
#include <d3d12.h>
#include<wrl.h>
#include<memory>
#include<array>

enum class BlendMode
{
	None,//ノーブレンド
	Alpha,//半透明合成
	Add,//加算合成
	Sub,//減算合成
	Mul,//乗算合成
	Inv//色反転
};

struct PipelineSet
{
	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// パイプランステートの生成
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

class Pipeline
{
public:

	static void CreateSpritePipline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend, ID3D12Device*device, std::array<PipelineSet, 6> &pip);

};