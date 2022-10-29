#include "WindowsApp.h"
#include <string>
#pragma comment(lib,"winmm.lib")

//ウインドウプロシージャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
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

void WindowsApp::CreatWindow(const wchar_t* title)
{
	//システムタイマーの分解能を上げる
	timeBeginPeriod(1);

	//ウインドウクラスの設定
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;//ウインドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";//ウインドウクラス名
	w.hInstance = GetModuleHandle(nullptr);//ウインドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指定

	//ウインドウクラスをOSに登録する
	RegisterClassEx(&w);

	//ウインドウサイズ{X座標　Y座標 横幅　縦幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウインドウオブジェクトの生成
	hwnd = CreateWindow(w.lpszClassName,//クラス名
		title,				//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,		//標準的なウインドウスタイル
		CW_USEDEFAULT,				//表示X座標(OSに任せる)
		CW_USEDEFAULT,				//表示Y座標(OSに任せる)
		wrc.right - wrc.left,		//ウインドウ横幅
		wrc.bottom - wrc.top,		//ウインドウ縦幅
		nullptr,					//親ウインドウハンドル
		nullptr,					//メニューハンドル
		w.hInstance,				//呼び出しアプリケーションハンドル
		nullptr);					//オプション

	//ウインドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

bool WindowsApp::MessageWindow()
{
	//メッセージがある？
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg); //キー入力メッセージの処理
		DispatchMessage(&msg); //プロシージャにメッセージを送る
	}

	//×ボタンで終了メッセージが来たらゲームループを抜ける
	if (msg.message == WM_QUIT) {
		return false;
	}
	return true;
}

void WindowsApp::Break() {
	//ウインドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}

WNDCLASSEX WindowsApp::GetW() {
	return w;
}

void WindowsApp::SetW(WNDCLASSEX W) {
	w = W;
}

HWND WindowsApp::GetHwnd() {
	return hwnd;
}

void WindowsApp::SetHwnd(HWND Hwnd) {
	hwnd = Hwnd;
}

int WindowsApp::GetWidth()
{
	return window_width;
}

int WindowsApp::GetHeight()
{
	return window_height;
}

WindowsApp* WindowsApp::GetInstance(){
	static WindowsApp instance;
	return &instance;
}