#pragma once
#include"myMath.h"
#include"DrawCommon.h"
#include"Camera.h"
#include <forward_list>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include<memory>
#include "TextureManager.h"
#include"Pipeline.h"
#include"Transform.h"

//パーティクル1粒
struct OneParticle
{
	//座標
	myMath::Vector3 position = {};
	//速度
	myMath::Vector3 velocity = {};
	//加速度
	myMath::Vector3 accel = {};
	//現在フレーム
	float flame = 0;
	//終了フレーム
	float num_flame = 0;
	//スケール
	float scale = 1.0f;
	//初期値
	float s_scale = 1.0f;
	//最終値
	float e_scale = 0.0f;
	//回転
	float rotation = 0.0f;
	float rotationSpeed = 0.0f;
	//カラー
	myMath::Vector4 color = {};
};

class ParticleManager
{
private:

	static Microsoft::WRL::ComPtr<ID3D12Device>sDevice_;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>sCmdList_;

	std::forward_list<OneParticle>particles_; //頂点数
	static const uint32_t vertexCount_ = 9192; //頂点数
	//頂点データ配列
	static PosScaleRotColor vertices_[vertexCount_];

	HRESULT result_ = S_FALSE;
	char PADING_[4] = {};

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//頂点マップ
	PosUvColor* vertMap_ = {};

	// 定数バッファ
	std::unique_ptr<ConstantBuffer> constBuffer_ = {};

	//定数バッファのマッピング用ポインタ
	matMatBillboard constBuffMap_ = {};

	TextureData* texture_ = {};

	BlendMode blendMode_ = BlendMode::Alpha;//初期値半透明合成
	static Blob sBlob_;//シェーダオブジェクト
	static std::array<PipelineSet, 6> sPip_;//パイプライン

public:

	ParticleManager();
	~ParticleManager();

	static void StaticInitialize();

	void Initialize(uint32_t handle);

	void Update(Camera* camera);

	void RandomXMoveUpdate(Camera* camera, float xMoveMin, float xMoveMax);

	void Add(float life, myMath::Vector3 position, myMath::Vector3 velocity, myMath::Vector3 accel, float start_scale, float end_scale, myMath::Vector4 color, float angle = 0.0f, float rotSpeed = 1.0f);
	
	void Draw();

	uint32_t LoadTexture(const std::string& filePath);

private:

	void CreateBuff();

	static void LoadShader();

	static void CreatePipline();

	void BlendSet(BlendMode mode);

	void DrawCommand();

	void BillboardUpdate(Camera* camera);
};