#include "Transform.h"
#include"DirectXBase.h"

myMath::Matrix4 Transform::sDefaultProjectionMat_ = { 1.3579f, 0.0f, 0.0f, 0.0f, 0.0f, 2.4142f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0001f, 1.0f, 0.0f, 0.0f, -0.1000f, 0.0f };
myMath::Matrix4 Transform::sDefaultViewMat_ = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f };

void Transform::Initialize()
{
	//定数バッファ生成(3D座標変換行列)
	constBuff_ = std::make_shared<ConstantBuffer>();
	constBuff_->Create(sizeof(worldViewpojCamera));

	//スケール、回転、平行移動行列の計算
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//ワールド行列の合成
	//変形をリセット
	matWorld = myMath::MakeIdentity();
	//ワールド行列にスケーリングを反映
	matWorld *= matScale;
	//ワールド行列に回転を反映
	matWorld *= matRot;
	//ワールド行列に平行移動を反映
	matWorld *= matTrans;
	//親行列の指定がある場合は、掛け算する
	if (parent)
	{
		matWorld *= parent->matWorld;
		matScale *= parent->matScale;
		matRot *= parent->matRot;
		matTrans *= parent->matTrans;
	}

	//定数バッファに書き込み
	constBuffMap_.matWorld = matWorld * sDefaultViewMat_ * sDefaultProjectionMat_;
	constBuffMap_.world = matWorld;
	constBuffMap_.cameraPos = { 0.0f,0.0f,-50.0f };

	constBuff_->Update(&constBuffMap_);
}

void Transform::TransUpdate(Camera* camera, myMath::Quaternion* q)
{
	//スケール、回転、平行移動行列の計算
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//ワールド行列の合成
	//変形をリセット
	matWorld = myMath::MakeIdentity();
	//ワールド行列にスケーリングを反映
	matWorld *= matScale;
	//ワールド行列に回転を反映
	matWorld *= matRot;
	if (q != nullptr)
	{
		matWorld *= q->Rotate();
	}
	//ワールド行列に平行移動を反映
	matWorld *= matTrans;
	//親行列の指定がある場合は、掛け算する
	if (parent)
	{
		matWorld *= parent->matWorld;
		matScale *= parent->matScale;
		matRot *= parent->matRot;
		matTrans *= parent->matTrans;
	}
	parentToTranslation.x = matWorld.m[3][0];
	parentToTranslation.y = matWorld.m[3][1];
	parentToTranslation.z = matWorld.m[3][2];

	//定数バッファに書き込み
	constBuffMap_.matWorld = matWorld * camera->GetMatViewInverse() * camera->GetMatProjection();
	constBuffMap_.world = matWorld;
	constBuffMap_.cameraPos = camera->GetEye();
	constBuff_->Update(&constBuffMap_);
}

void Transform::Update()
{
	constBuff_->Update(&constBuffMap_);
}

void Transform::MakeWorldMatrix()
{
	//スケール、回転、平行移動行列の計算
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//ワールド行列の合成
	//変形をリセット
	matWorld = myMath::MakeIdentity();
	//ワールド行列にスケーリングを反映
	matWorld *= matScale;
	//ワールド行列に回転を反映
	matWorld *= matRot;
	//ワールド行列に平行移動を反映
	matWorld *= matTrans;
	//親行列の指定がある場合は、掛け算する
	if (parent)
	{
		matWorld *= parent->matWorld;
		matScale *= parent->matScale;
		matRot *= parent->matRot;
		matTrans *= parent->matTrans;
	}
}

ID3D12Resource* Transform::GetconstBuff()
{
	return constBuff_->GetResource();
}

worldViewpojCamera* Transform::GetWorldViewpojCamera()
{
	return &constBuffMap_;
}

namespace myMath
{
	Matrix4 MakeWorldMatrix4(Transform& transform)
	{
		Matrix4 matWorld = MakeIdentity();

		Matrix4 matScal, matRot, matTrans;

		//スケーリング倍率
		matScal.MakeScaling(transform.scale);

		//回転行列
		matRot.MakeRotation(transform.rotation);

		// matWorld_に移動量を掛け算
		matTrans.MakeTranslation(transform.translation);

		matWorld = matScal * matRot * matTrans;

		if (transform.parent)
		{
			matWorld *= transform.parent->matWorld;
		}

		return matWorld;
	}

	Vector3 GetWorldPosition(Transform& transform)
	{
		//ワールド座標を入れる変数
		Vector3 worldPos;
		//ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = transform.matWorld.m[3][0];
		worldPos.y = transform.matWorld.m[3][1];
		worldPos.z = transform.matWorld.m[3][2];

		return worldPos;
	}
}