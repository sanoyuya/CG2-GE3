#include "ImGuiManager.h"
#include"imgui.h"
#include<imgui_impl_win32.h>
#include<imgui_impl_dx12.h>
#include"WindowsApp.h"
#include"DirectXBase.h"
#include"DescriptorHeap.h"

ImGuiManager* imGuiInstance = nullptr;

void ImGuiManager::Initialize()
{
	//ImGuiのコンテキストを生成
	ImGui::CreateContext();
	//ImGuiのスタイルを設定
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(WindowsApp::GetInstance()->GetHwnd());

	DescriptorHeap::DescriptorHeapViewHandle handle = DirectXBase::GetInstance()->GetDescriptorHeap()->AddSRV();

	ImGui_ImplDX12_Init(
		DirectXBase::GetInstance()->GetDevice().Get(),
		static_cast<int>(DirectXBase::GetInstance()->GetBackBuffer()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DirectXBase::GetInstance()->GetDescriptorHeap()->GetHeap().Get(),
		handle.cpuHandle,
		handle.gpuHandle
	);

	ImGuiIO& io = ImGui::GetIO();
	//標準フォントを追加する
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Destroy()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete imGuiInstance;
}

void ImGuiManager::Begin()
{
	//ImGuiフレーム開始
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	DirectXBase::GetInstance()->GetCommandList()->SetDescriptorHeaps(1, DirectXBase::GetInstance()->GetDescriptorHeap()->GetHeap().GetAddressOf());
	//描画コマンド実行
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DirectXBase::GetInstance()->GetCommandList().Get());
}

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager instance;
	return &instance;
}