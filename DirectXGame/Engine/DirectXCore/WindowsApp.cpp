#include "WindowsApp.h"
#include <string>
#include<imgui_impl_win32.h>

#pragma comment(lib,"winmm.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam);

//�E�C���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}

	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {
		//�E�C���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��āA�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WindowsApp::CreatWindow(const wchar_t* title, const float width, const float height)
{
	windowWidth_ = width;
	windowHeight_ = height;

	//�V�X�e���^�C�}�[�̕���\���グ��
	timeBeginPeriod(1);

	//�E�C���h�E�N���X�̐ݒ�
	w_.cbSize = sizeof(WNDCLASSEX);
	w_.lpfnWndProc = (WNDPROC)WindowProc;//�E�C���h�E�v���V�[�W����ݒ�
	w_.lpszClassName = L"DirectXGame";//�E�C���h�E�N���X��
	w_.hInstance = GetModuleHandle(nullptr);//�E�C���h�E�n���h��
	w_.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��

	//�E�C���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w_);

	//�E�C���h�E�T�C�Y{X���W�@Y���W �����@�c��}
	RECT wrc = { 0,0,static_cast<LONG>(windowWidth_),static_cast<LONG>(windowHeight_) };
	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�C���h�E�I�u�W�F�N�g�̐���
	hwnd_ = CreateWindow(w_.lpszClassName,//�N���X��
		title,				//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,		//�W���I�ȃE�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,				//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,		//�E�C���h�E����
		wrc.bottom - wrc.top,		//�E�C���h�E�c��
		nullptr,					//�e�E�C���h�E�n���h��
		nullptr,					//���j���[�n���h��
		w_.hInstance,				//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);					//�I�v�V����
}

bool WindowsApp::MessageWindow()
{
	//���b�Z�[�W������H
	if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg_); //�L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg_); //�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (msg_.message == WM_QUIT) {
		return false;
	}
	return true;
}

void WindowsApp::Appearance()
{
	//�E�C���h�E��\����Ԃɂ���
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
	//�E�C���h�E�N���X��o�^����
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