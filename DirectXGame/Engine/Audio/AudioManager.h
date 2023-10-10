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

class AudioData
{
public:
	std::string filePass_;
	IMFSourceReader* pMFSourceReader_ = nullptr;
	WAVEFORMATEX* waveFormat_ = nullptr;
	std::vector<BYTE> mediaData_;
	std::unique_ptr<char> pBuffer_;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;
	float volume_ = 1.0f;
	bool loop_ = false;
	bool playTrigger_ = false;
	char PADDING2_[2]{};
	AudioData(std::string FilePass);
	void Unload();
};

class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:

	virtual ~XAudio2VoiceCallback()
	{
	};

	//ボイス処理パスの開始時
	STDMETHOD_(void, OnVoiceProcessingPassStart)(THIS_ UINT32 BytesRequired)
	{
		static_cast<void>(BytesRequired);
	};

	//ボイス処理パスの終了時
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS)
	{
	};

	//バッファストリームの再生が終了したとき
	STDMETHOD_(void, OnStreamEnd) (THIS)
	{
	};

	//バッファの使用開始時
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);

	};

	//バッファの末尾に達した時
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);
	};

	//再生がループ位置に達した時
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext)
	{
		static_cast<void>(pBufferContext);
	};

	//ボイスの実行エラー時
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
	/// 再生されているか
	/// </summary>
	/// <param name="handle">サウンドデータ</param>
	/// <returns></returns>
	bool NowPlay(const uint32_t handle);

	/// <summary>
	/// 音量変更
	/// </summary>
	/// <param name="handle">サウンドデータ</param>
	/// <param name="volume">音の大きさ ( 0 ～ 1.0f )</param>
	void ChangeVolume(const uint32_t handle, float volume);

	/// <summary>
	/// 現在の音量の取得
	/// </summary>
	/// <param name="handle">サウンドデータ</param>
	/// <returns></returns>
	float GetVolume(const uint32_t handle);

	/// <summary>
	/// サウンド読み込み
	/// </summary>
	/// <param name="fileName">サウンドデータ</param>
	/// <param name="volume">音の大きさ ( 0 ～ 1.0f )</param>
	/// <returns></returns>
	uint32_t LoadAudio(std::string fileName, const float volume = 1.0f);

	/// <summary>
	/// サウンドを再生する
	/// </summary>
	/// <param name="handle">サウンドデータ</param>
	/// <param name="loopFlag">ループするかしないか(ループするならtrue)</param>
	/// <returns></returns>
	int32_t PlayWave(const uint32_t handle, bool loopFlag = false);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="handles">サウンドデータ</param>
	/// <returns></returns>
	int32_t PlayWaveArray(const std::vector<uint32_t>& handles);

	/// <summary>
	/// サウンドを止める
	/// </summary>
	/// <param name="handle">サウンドデータ</param>
	void StopWave(const uint32_t handle);

private:
	AudioManager();
	~AudioManager();

	//コピーコンストラクタ・代入演算子削除
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager(const AudioManager&) = delete;
};