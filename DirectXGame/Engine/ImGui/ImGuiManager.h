#pragma once
#include<memory>
#include<wrl.h>
#include"DescriptorHeap.h"
#include"WindowsApp.h"

class ImGuiManager
{
private:

	//SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvHeap;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// �������
	/// </summary>
	void Destroy();

	/// <summary>
	/// ImGui��t�J�n
	/// </summary>
	void Begin();

	/// <summary>
	/// ImGui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	//�V���O���g��
	static ImGuiManager* GetInstance();

private:

	ImGuiManager() = default;
	~ImGuiManager() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ImGuiManager& operator=(const ImGuiManager&) = delete;
	ImGuiManager(const ImGuiManager&) = delete;
};