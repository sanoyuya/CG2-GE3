#pragma once
#include <chrono>

class FPS
{
private:

	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference;

public:

	void Initialize();

	/// <summary>
	/// fps固定の更新処理
	/// </summary>
	/// <param name="fixedFps">fps固定値</param>
	/// <param name="flag">半端なモニターかどうか(半端ならtrue)</param>
	void Update(float fixedFps = 60.0f, bool flag = true);

};