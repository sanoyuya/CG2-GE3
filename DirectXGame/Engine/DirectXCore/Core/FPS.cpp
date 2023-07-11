#include "FPS.h"

void FPS::Initialize()
{
	reference_ = std::chrono::steady_clock::now();//現在の時間を代入
}

void FPS::Update(float fixedFps, bool flag)
{
	//1/fixedFps秒ぴったり
	std::chrono::microseconds minTime(uint64_t(1000000.0f / fixedFps));
	//1/fixedFps秒よりわずかに短い時間
	std::chrono::microseconds minCheckTime(uint64_t(1000000.0f / (fixedFps + 5.0f)));

	//現在時間を取得
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	//前回記録からの経過時間を取得する
	std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	if (flag == false)
	{
		//1/fixedFps秒(よりわずかに短い時間)経っていない場合
		if (elapsed < minTime)
		{
			//1/fixedFps秒経過するまで微小なスリープを繰り返す
			while (std::chrono::steady_clock::now() - reference_ < minTime)
			{
				//1マイクロ秒スリープ
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
	}
	else
	{
		//1/fixedFps秒(よりわずかに短い時間)経っていない場合
		if (elapsed < minCheckTime)
		{
			//1/fixedFps秒経過するまで微小なスリープを繰り返す
			while (std::chrono::steady_clock::now() - reference_ < minCheckTime)
			{
				//1マイクロ秒スリープ
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
	}
	
	//現在の時間を記録する
	reference_ = std::chrono::steady_clock::now();
}