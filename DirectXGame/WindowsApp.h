#pragma once
#include<Windows.h>
class WindowsApp
{
private:
	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};//メッセージ
	float window_width = 1280;//横幅
	float window_height = 720;//縦幅
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

	//シングルトン
	static WindowsApp* GetInstance();
};