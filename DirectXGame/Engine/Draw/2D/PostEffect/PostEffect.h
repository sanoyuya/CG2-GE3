#pragma once
#include"WindowsApp.h"
#include"DirectXBase.h"
#include "Sprite2D.h"
#include"myMath.h"

class PostEffect : public Sprite2D
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_;

	DescriptorHeap::DescriptorHeapViewHandle handle_;

	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>depthBuff_;
	//RTV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapRTV_;
	//DSV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapDSV_;

	//画面クリアカラー
	static const float sClearColor_[4];

	myMath::Vector2 position_ = { 0.0f,0.0f };
	myMath::Vector2 scale_ = { 0.0f,0.0f };
	float rotation_ = 0.0f;
	myMath::Vector4 color_ = { 0.0f,0.0f,0.0f,0.0f };
	myMath::Vector2 anchorpoint_ = { 0.0f,0.0f };
	bool flipX_ = false;
	bool flipY_ = false;

	uint32_t tex_ = 0;

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	void PreDrawScene(WindowsApp* windowsApp);

	/// <summary>
	/// シーン描画処理後
	/// </summary>
	void PostDrawScene();

private:

	//texBuff_の生成
	void CreateTexBuff(WindowsApp* windowsApp);
	//SRVの作成
	void CreateDescHeap();
	//RTVの作成
	void CreateRTV();
	//深度バッファの生成
	void CreateDepth(WindowsApp* windowsApp);
	//DSVの作成
	void CreateDSV();
};