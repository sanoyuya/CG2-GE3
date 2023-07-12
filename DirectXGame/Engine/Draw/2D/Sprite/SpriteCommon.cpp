#include "SpriteCommon.h"

Microsoft::WRL::ComPtr<ID3D12Device>SpriteCommon::sDevice_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>SpriteCommon::sCmdList_;
Blob SpriteCommon::sBlob_;//シェーダオブジェクト
std::array<PipelineSet, 6> SpriteCommon::sPip_;

void SpriteCommon::StaticInitialize()
{
	sDevice_ = DirectXBase::GetInstance()->GetDevice();
	sCmdList_ = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();

	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateSpritePipline(sBlob_, (BlendMode)i, sDevice_.Get(), sPip_);
	}
}

void SpriteCommon::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	sBlob_.vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Sprite/SpriteVS.hlsl", "main", "vs_5_0", sBlob_.vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_.ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Sprite/SpritePS.hlsl", "main", "ps_5_0", sBlob_.ps.Get());
}

void SpriteCommon::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		sCmdList_->SetPipelineState(sPip_[0].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		sCmdList_->SetPipelineState(sPip_[1].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		sCmdList_->SetPipelineState(sPip_[2].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		sCmdList_->SetPipelineState(sPip_[3].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		sCmdList_->SetPipelineState(sPip_[4].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		sCmdList_->SetPipelineState(sPip_[5].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[5].rootSignature.Get());

		break;
	}
}

void SpriteCommon::DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff)
{
	// プリミティブ形状の設定コマンド
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	sCmdList_->SetGraphicsRootConstantBufferView(0, constBuff->GetAddress());
	//SRVヒープの設定コマンド
	sCmdList_->SetDescriptorHeaps(1, textureData->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	sCmdList_->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	sCmdList_->IASetIndexBuffer(&ibView);

	// 描画コマンド
	sCmdList_->DrawIndexedInstanced(6, 1, 0, 0, 0);
}