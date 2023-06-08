#pragma once
#include<Windows.h>
class WindowsApp
{
private:

	WNDCLASSEX w{};
	HWND hwnd;
	MSG msg{};//メッセージ
	float window_width = 1280.0f;//横幅
	float window_height = 720.0f;//縦幅

public:

	//デストラクタ
	~WindowsApp();

	/// <summary>
	/// ウィンドウの作成
	/// </summary>
	/// <param name="title"></param>
	/// <param name="width">ウィンドウの横幅の大きさ</param>
	/// <param name="height">ウィンドウの縦幅の大きさ</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", const float width = 1280.0f, const float height = 720.0f);
	bool MessageWindow();
	void Appearance();

	//ゲッター
	WNDCLASSEX GetW();
	HWND GetHwnd();
	float GetWidth();
	float GetHeight();

	//セッター
	void SetW(WNDCLASSEX W);
	void SetHwnd(HWND Hwnd);
};