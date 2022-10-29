#include "WindowsApp.h"
#include <string>
#pragma comment(lib,"winmm.lib")

//�E�C���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
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

void WindowsApp::CreatWindow(const wchar_t* title)
{
	//�V�X�e���^�C�}�[�̕���\���グ��
	timeBeginPeriod(1);

	//�E�C���h�E�N���X�̐ݒ�
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;//�E�C���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"DirectXGame";//�E�C���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);//�E�C���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��

	//�E�C���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);

	//�E�C���h�E�T�C�Y{X���W�@Y���W �����@�c��}
	RECT wrc = { 0,0,window_width,window_height };
	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�C���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(w.lpszClassName,//�N���X��
		title,				//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,		//�W���I�ȃE�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,				//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,		//�E�C���h�E����
		wrc.bottom - wrc.top,		//�E�C���h�E�c��
		nullptr,					//�e�E�C���h�E�n���h��
		nullptr,					//���j���[�n���h��
		w.hInstance,				//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);					//�I�v�V����

	//�E�C���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

bool WindowsApp::MessageWindow()
{
	//���b�Z�[�W������H
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg); //�L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg); //�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (msg.message == WM_QUIT) {
		return false;
	}
	return true;
}

void WindowsApp::Break() {
	//�E�C���h�E�N���X��o�^����
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