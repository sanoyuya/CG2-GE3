#pragma once
#include<Windows.h>
class WindowsApp
{
private:
	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};//���b�Z�[�W
	const int window_width = 1280;//����
	const int window_height = 720;//�c��
public:
	void CreatWindow();
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