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
	void CreatWindow(const wchar_t* title = L"DirectXGame", const int width = 1280, const int height = 720);
	bool MessageWindow();
	void Break();
	WNDCLASSEX GetW();
	void SetW(WNDCLASSEX W);
	HWND GetHwnd();
	void SetHwnd(HWND Hwnd);
	int GetWidth();
	int GetHeight();

	//�V���O���g��
	static WindowsApp* GetInstance();
};