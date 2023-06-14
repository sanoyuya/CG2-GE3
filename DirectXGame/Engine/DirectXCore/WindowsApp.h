#pragma once
#include<Windows.h>

class WindowsApp
{
private:

	WNDCLASSEX w_{};
	HWND hwnd_;
	MSG msg_{};//���b�Z�[�W
	float windowWidth_ = 1280.0f;//����
	float windowHeight_ = 720.0f;//�c��

public:

	//�f�X�g���N�^
	~WindowsApp();

	/// <summary>
	/// �E�B���h�E�̍쐬
	/// </summary>
	/// <param name="title"></param>
	/// <param name="width">�E�B���h�E�̉����̑傫��</param>
	/// <param name="height">�E�B���h�E�̏c���̑傫��</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", const float width = 1280.0f, const float height = 720.0f);
	bool MessageWindow();
	void Appearance();

	//�Q�b�^�[
	WNDCLASSEX GetW();
	HWND GetHwnd();
	float GetWidth();
	float GetHeight();

	//�Z�b�^�[
	void SetW(WNDCLASSEX W);
	void SetHwnd(HWND Hwnd);
};