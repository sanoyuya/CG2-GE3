#pragma once
#include<memory>
#include<wrl.h>
#include"DescriptorHeap.h"
#include"WindowsApp.h"

class ImGuiManager
{
private:

	//SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvHeap;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// 解放処理
	/// </summary>
	void Destroy();

	/// <summary>
	/// ImGui受付開始
	/// </summary>
	void Begin();

	/// <summary>
	/// ImGui受付終了
	/// </summary>
	void End();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	//シングルトン
	static ImGuiManager* GetInstance();

private:

	ImGuiManager() = default;
	~ImGuiManager() = default;

	//コピーコンストラクタ・代入演算子削除
	ImGuiManager& operator=(const ImGuiManager&) = delete;
	ImGuiManager(const ImGuiManager&) = delete;
};