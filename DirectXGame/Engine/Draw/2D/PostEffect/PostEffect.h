#pragma once
#include"WindowsApp.h"
#include"DirectXBase.h"
#include "Sprite2D.h"
#include"myMath.h"

class PostEffect : public Sprite2D
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapSRV_;

	myMath::Vector2 position_ = { 0.0f,0.0f };
	myMath::Vector2 scale_ = { 0.0f,0.0f };
	float rotation_ = 0.0f;
	myMath::Vector4 color_ = { 0.0f,0.0f,0.0f,0.0f };
	myMath::Vector2 anchorpoint_ = { 0.0f,0.0f };
	bool flipX_ = false;
	bool flipY_ = false;

	uint32_t tex_ = 0;

	DescriptorHeap::DescriptorHeapViewHandle handle_;

public:

	/// <summary>
	/// èâä˙âªèàóù
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// ï`âÊèàóù
	/// </summary>
	void Draw();

private:

	void CreateTexBuff(WindowsApp* windowsApp);

	void CreateDescHeap();
};