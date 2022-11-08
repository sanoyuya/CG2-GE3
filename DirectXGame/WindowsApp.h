#pragma once
#include<Windows.h>
class WindowsApp
{
private:

	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};//���b�Z�[�W
	float window_width = 1280;//����
	float window_height = 720;//�c��

public:

	/// <summary>
	/// �E�B���h�E�̍쐬
	/// </summary>
	/// <param name="title"></param>
	/// <param name="width">�E�B���h�E�̉����̑傫��</param>
	/// <param name="height">�E�B���h�E�̏c���̑傫��</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", const int width = 1280, const int height = 720);
	bool MessageWindow();
	void Break();

	//�Q�b�^�[
	WNDCLASSEX GetW();
	HWND GetHwnd();
	int GetWidth();
	int GetHeight();

	//�Z�b�^�[
	void SetW(WNDCLASSEX W);
	void SetHwnd(HWND Hwnd);

	//�V���O���g��
	static WindowsApp* GetInstance();

private:

	WindowsApp() = default;
	~WindowsApp() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	WindowsApp& operator=(const WindowsApp&) = delete;
	WindowsApp(const WindowsApp&) = delete;
};