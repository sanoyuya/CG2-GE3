#include "WindowsApp.h"
#include <string>
#include<imgui_impl_win32.h>

#pragma comment(lib,"winmm.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam);

//ウインドウプロシージャ
LRESULT WindowProc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		//ウインドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WindowsApp::CreatWindow(const wchar_t* title, const float width, const float height)
{
	windowWidth_ = width;
	windowHeight_ = height;

	//システムタイマーの分解能を上げる
	timeBeginPeriod(1);

	//ウインドウクラスの設定
	w_.cbSize = sizeof(WNDCLASSEX);
	w_.lpfnWndProc = (WNDPROC)WindowProc;//ウインドウプロシージャを設定
	w_.lpszClassName = L"DirectXGame";//ウインドウクラス名
	w_.hInstance = GetModuleHandle(nullptr);//ウインドウハンドル
	w_.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指定

	//ウインドウクラスをOSに登録する
	RegisterClassEx(&w_);

	//ウインドウサイズ{X座標　Y座標 横幅　縦幅}
	RECT wrc = { 0,0,static_cast<LONG>(windowWidth_),static_cast<LONG>(windowHeight_) };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウインドウオブジェクトの生成
	hwnd_ = CreateWindow(w_.lpszClassName,//クラス名
		title,				//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,		//標準的なウインドウスタイル
		CW_USEDEFAULT,				//表示X座標(OSに任せる)
		CW_USEDEFAULT,				//表示Y座標(OSに任せる)
		wrc.right - wrc.left,		//ウインドウ横幅
		wrc.bottom - wrc.top,		//ウインドウ縦幅
		nullptr,					//親ウインドウハンドル
		nullptr,					//メニューハンドル
		w_.hInstance,				//呼び出しアプリケーションハンドル
		nullptr);					//オプション
}

bool WindowsApp::MessageWindow()
{
	//メッセージがある？
	if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg_); //キー入力メッセージの処理
		DispatchMessage(&msg_); //プロシージャにメッセージを送る
	}

	//×ボタンで終了メッセージが来たらゲームループを抜ける
	if (msg_.message == WM_QUIT) {
		return false;
	}
	return true;
}

void WindowsApp::Appearance()
{
	//ウインドウを表示状態にする
	ShowWindow(hwnd_, SW_SHOW);
}

WNDCLASSEX WindowsApp::GetW() {
	return w_;
}

void WindowsApp::SetW(WNDCLASSEX W) {
	w_ = W;
}

HWND WindowsApp::GetHwnd() {
	return hwnd_;
}

void WindowsApp::SetHwnd(HWND Hwnd) {
	hwnd_ = Hwnd;
}

WindowsApp::~WindowsApp()
{
	//ウインドウクラスを登録解除
	UnregisterClass(w_.lpszClassName, w_.hInstance);
}

float WindowsApp::GetWidth()
{
	return windowWidth_;
}

float WindowsApp::GetHeight()
{
	return windowHeight_;
}