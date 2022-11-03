#pragma once
#include<cassert>
#include<dxgi1_6.h>
#include<dxgidebug.h>
#include<filesystem>
#include<forward_list>
#include<fstream>
#include<iterator>
#include<memory>
#include<mmsystem.h>
#include<sstream>
#include<string>
#include<tchar.h>
#include<mfapi.h>
#include<mfidl.h>
#include<mfreadwrite.h>
#include<unordered_map>
#include<vector>
#include<xaudio2.h>
#include<Windows.h>
#include<wrl.h>

#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

class AudioData
{
public:
	std::string filePass;
	IMFSourceReader* pMFSourceReader = nullptr;
	WAVEFORMATEX* waveFormat = nullptr;
	std::vector<BYTE> mediaData;
	char* pBuffer = nullptr;
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	float volume = 1.0f;
	bool loop = false;
	bool playTrigger = false;
	char PADDING2[2]{};
	AudioData(std::string FilePass);
	void Unload();
};

class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:

	virtual ~XAudio2VoiceCallback()
	{
	};

	//�{�C�X�����p�X�̊J�n��
	STDMETHOD_(void, OnVoiceProcessingPassStart)(THIS_ UINT32 BytesRequired)
	{
		static_cast<void>(BytesRequired);
	};

	//�{�C�X�����p�X�̏I����
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS)
	{
	};

	//�o�b�t�@�X�g���[���̍Đ����I�������Ƃ�
	STDMETHOD_(void, OnStreamEnd) (THIS)
	{
	};

	//�o�b�t�@�̎g�p�J�n��
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);

	};

	//�o�b�t�@�̖����ɒB������
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);
	};

	//�Đ������[�v�ʒu�ɒB������
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);
	};

	//�{�C�X�̎��s�G���[��
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error)
	{
		static_cast<void>(pBufferContext);
		static_cast<void>(Error);
	};
};

struct PlayAudioArray
{
	std::vector<uint32_t>handles;
	int32_t nowIdx = 0;
	char PADDING[4]{};
	PlayAudioArray(const std::vector<uint32_t>& Handles);
};

class AudioManager
{
private:
	static AudioManager* instance;
	Microsoft::WRL::ComPtr<IXAudio2>xAudio2;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	XAudio2VoiceCallback voiceCallback;
	std::list<AudioData>audios;
	std::vector<PlayAudioArray>playHandleArray;

public:

	static AudioManager* GetInstance();
	void Destroy();

	void Initialize();
	void Update();

	/// <summary>
	/// �Đ�����Ă��邩
	/// </summary>
	/// <param name="handle">�T�E���h�f�[�^</param>
	/// <returns></returns>
	bool NowPlay(const uint32_t& handle);

	/// <summary>
	/// ���ʕύX
	/// </summary>
	/// <param name="handle">�T�E���h�f�[�^</param>
	/// <param name="volume">���̑傫�� ( 0 �` 1.0f )</param>
	void ChangeVolume(const uint32_t& handle, float volume);

	/// <summary>
	/// ���݂̉��ʂ̎擾
	/// </summary>
	/// <param name="handle">�T�E���h�f�[�^</param>
	/// <returns></returns>
	float GetVolume(const uint32_t& handle);

	/// <summary>
	/// �T�E���h�ǂݍ���
	/// </summary>
	/// <param name="fileName">�T�E���h�f�[�^</param>
	/// <param name="volume">���̑傫�� ( 0 �` 1.0f )</param>
	/// <returns></returns>
	uint32_t LoadAudio(std::string fileName, const float& volume = 1.0f);

	/// <summary>
	/// �T�E���h���Đ�����
	/// </summary>
	/// <param name="handle">�T�E���h�f�[�^</param>
	/// <param name="loopFlag">���[�v���邩���Ȃ���(���[�v����Ȃ�true)</param>
	/// <returns></returns>
	int32_t PlayWave(const uint32_t& handle, bool loopFlag = false);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="handles">�T�E���h�f�[�^</param>
	/// <returns></returns>
	int32_t PlayWaveArray(const std::vector<uint32_t>& handles);

	/// <summary>
	/// �T�E���h���~�߂�
	/// </summary>
	/// <param name="handle">�T�E���h�f�[�^</param>
	void StopWave(const uint32_t& handle);

private:
	AudioManager();
	~AudioManager();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager(const AudioManager&) = delete;
};