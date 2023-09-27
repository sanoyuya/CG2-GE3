#pragma once

/// <summary>
/// ステージのベース
/// </summary>
class BaseStage
{
public:

	virtual ~BaseStage() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//終了処理
	virtual void Destroy() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;
};