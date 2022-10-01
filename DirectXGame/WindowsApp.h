#pragma once
#include<Windows.h>
class WindowsApp
{
private:
	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};//メッセージ
	const int window_width = 1280;//横幅
	const int window_height = 720;//縦幅
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

	//シングルトン
	static WindowsApp* GetInstance();
};