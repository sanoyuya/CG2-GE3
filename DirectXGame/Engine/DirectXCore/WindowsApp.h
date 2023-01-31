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

	/// <summary>
	/// ウィンドウの作成
	/// </summary>
	/// <param name="title"></param>
	/// <param name="width">ウィンドウの横幅の大きさ</param>
	/// <param name="height">ウィンドウの縦幅の大きさ</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", const int width = 1280, const int height = 720);
	bool MessageWindow();
	void Break();

	//ゲッター
	WNDCLASSEX GetW();
	HWND GetHwnd();
	int GetWidth();
	int GetHeight();

	//セッター
	void SetW(WNDCLASSEX W);
	void SetHwnd(HWND Hwnd);

	//シングルトン
	static WindowsApp* GetInstance();

private:

	WindowsApp() = default;
	~WindowsApp() = default;

	//コピーコンストラクタ・代入演算子削除
	WindowsApp& operator=(const WindowsApp&) = delete;
	WindowsApp(const WindowsApp&) = delete;
};