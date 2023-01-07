#pragma once

//ゲーム全体
class YFramework
{
public:

	virtual ~YFramework() = default;

	//初期化処理
	virtual void Initialize();

	//終了処理
	virtual void Destroy();

	//更新処理
	virtual void Update();

	//描画処理
	virtual void Draw() = 0;

	//実行処理
	void Run();
};