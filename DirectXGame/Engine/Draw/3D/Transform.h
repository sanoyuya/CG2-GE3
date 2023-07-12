#pragma once
#include<memory>
#include"myMath.h"
#include"Camera.h"
#include"ConstantBuffer.h"
#include"DrawCommon.h"

class Transform
{
private:

	// 定数バッファ
	std::shared_ptr<ConstantBuffer> constBuff_;
	//定数バッファのマッピング用ポインタ
	worldViewpojCamera constBuffMap_;

	//初期化用のビュー行列計算
	static myMath::Matrix4 sDefaultViewMat_;

	//初期化用のプロジェクション行列計算
	static myMath::Matrix4 sDefaultProjectionMat_;

public:

	// ローカル座標
	myMath::Vector3 translation = { 0.0f, 0.0f, 0.0f };
	// X,Y,Z軸回りのローカル回転角
	myMath::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	// ローカルスケール
	myMath::Vector3 scale = { 1.0f, 1.0f, 1.0f };

	myMath::Matrix4 matWorld;

	// 親となるワールド変換へのポインタ
	const Transform* parent = nullptr;

	myMath::Vector3 parentToTranslation = { 0.0f, 0.0f, 0.0f };

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 行列を転送する
	/// </summary>
	void TransUpdate(Camera* camera);

	void Update();

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();
};

namespace myMath
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ワールド座標取得
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}
