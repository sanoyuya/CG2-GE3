#include "SpriteCommon.h"

Microsoft::WRL::ComPtr<ID3D12Device>SpriteCommon::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>SpriteCommon::cmdList;
Blob SpriteCommon::blob;//シェーダオブジェクト
std::array<PipelineSet, 6> SpriteCommon::pip;

void SpriteCommon::StaticInitialize()
{
	device = DirectXBase::GetInstance()->GetDevice();
	cmdList = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateSpritePipline(blob, (BlendMode)i, device.Get(), pip);
	}
}

void SpriteCommon::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	blob.vs = DrawCommon::ShaderCompile(L"Resources/shaders/SpriteVS.hlsl", "main", "vs_5_0", blob.vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	blob.ps = DrawCommon::ShaderCompile(L"Resources/shaders/SpritePS.hlsl", "main", "ps_5_0", blob.ps.Get());
}

void SpriteCommon::BlendSet(BlendMode mode)
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

void SpriteCommon::DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff)
{
	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, textureData->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}