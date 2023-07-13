#include "ParticleManager.h"

PosScaleColor ParticleManager::vertices_[vertexCount_];
Microsoft::WRL::ComPtr<ID3D12Device>ParticleManager::sDevice_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>ParticleManager::sCmdList_;
Blob ParticleManager::sBlob_;//シェーダオブジェクト
std::array<PipelineSet, 6> ParticleManager::sPip_;

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::StaticInitialize()
{
	sDevice_ = DirectXBase::GetInstance()->GetDevice();
	sCmdList_ = DirectXBase::GetInstance()->GetCommandList();

	LoadShader();
	CreatePipline();
}

void ParticleManager::Initialize(uint32_t handle)
{
	texture_ = TextureManager::GetTextureData(handle);
	CreateBuff();
}

void ParticleManager::Update(Camera* camera,Transform& transform)
{
	//寿命が尽きたパーティクルを全削除
	particles_.remove_if([](OneParticle& x)
		{
			return x.flame >= x.num_flame;
		}
	);

	//全パーティクル更新
	for (std::forward_list<OneParticle>::iterator it = particles_.begin();
		it != particles_.end();
		it++)
	{
		//経過フレーム数をカウント
		it->flame++;
		//速度に加速度を加算
		it->velocity = it->velocity + it->accel;
		//速度による移動
		it->position = it->position + it->velocity;

		//進行度を0～1の範囲に換算
		float f = (float)it->flame / it->num_flame;
		//スケールの線形補間
		it->scale = (it->e_scale - it->s_scale) * f;
		it->scale += it->s_scale;

		it->color.x -= 5.0f;
		it->color.y -= 5.0f;
		it->color.z -= 5.0f;
		it->color.w -= 5.0f;
	}

	//定数バッファへデータ転送
	PosScaleColor* vertMap = nullptr;
	vertMap = new PosScaleColor;

	//パーティクルの情報を1つずつ反映
	for (std::forward_list<OneParticle>::iterator it = particles_.begin();it != particles_.end();it++)
	{
		//座標
		vertMap->pos = it->position;
		//スケール
		vertMap->scale = it->scale;
		//カラー
		vertMap->color = it->color;
		//次の頂点へ
		vertMap++;
	}
	vertexBuffer_->Update(vertMap);

	BillboardUpdate(camera, transform);
}

void ParticleManager::Add(float life, myMath::Vector3 position, myMath::Vector3 velocity, myMath::Vector3 accel, float start_scale, float end_scale, myMath::Vector4 color)
{
	//リストに要素を追加
	particles_.emplace_front();
	//追加した要素の参照
	OneParticle& p = particles_.front();
	//値のセット
	p.position = position;
	p.velocity = velocity;
	p.accel = accel;
	p.num_flame = life;
	p.s_scale = start_scale;
	p.e_scale = end_scale;
	p.color = color;
}

void ParticleManager::Draw()
{
	//ブレンドモードに対応
	BlendSet(blendMode_);
	//描画コマンド
	DrawCommand();
}

uint32_t ParticleManager::LoadTexture(const std::string& filePath)
{
	return TextureManager::GetInstance()->LoadTexture(filePath);
}

void ParticleManager::CreateBuff()
{
	for (int i = 0; i < vertexCount_; i++)
	{
		//x,y,z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_width = 10.0f;
		vertices_[i].pos.x = (float)rand() / RAND_MAX * rnd_width - rnd_width / 2.0f;
		vertices_[i].pos.y = (float)rand() / RAND_MAX * rnd_width - rnd_width / 2.0f;
		vertices_[i].pos.z = (float)rand() / RAND_MAX * rnd_width - rnd_width / 2.0f;
	}

	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(vertexCount_, sizeof(PosScaleColor));
	vertexBuffer_->Update(vertices_);

	constBuffer_ = std::make_unique<ConstantBuffer>();
	constBuffer_->Create(sizeof(myMath::Matrix4));
}

void ParticleManager::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	sBlob_.vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Particle/ParticleVS.hlsl", "main", "vs_5_0", sBlob_.vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_.ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Particle/ParticlePS.hlsl", "main", "ps_5_0", sBlob_.ps.Get());
	//ピクセルシェーダの読み込みとコンパイル
	sBlob_.gs = DrawCommon::ShaderCompile(L"Resources/Shaders/Particle/ParticleGS.hlsl", "main", "gs_5_0", sBlob_.gs.Get());
}

void ParticleManager::CreatePipline()
{
	for (int8_t i = 0; i < sPip_.size(); i++)
	{
		Pipeline::CreateParticlePipline(sBlob_, (BlendMode)i, sDevice_.Get(), sPip_);
	}
}

void ParticleManager::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:
		sCmdList_->SetPipelineState(sPip_[0].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[0].rootSignature.Get());
		break;
	case BlendMode::Alpha:
		sCmdList_->SetPipelineState(sPip_[1].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[1].rootSignature.Get());
		break;
	case BlendMode::Add:
		sCmdList_->SetPipelineState(sPip_[2].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[2].rootSignature.Get());
		break;
	case BlendMode::Sub:
		sCmdList_->SetPipelineState(sPip_[3].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[3].rootSignature.Get());
		break;
	case BlendMode::Mul:
		sCmdList_->SetPipelineState(sPip_[4].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[4].rootSignature.Get());
		break;
	case BlendMode::Inv:
		sCmdList_->SetPipelineState(sPip_[5].pipelineState.Get());
		sCmdList_->SetGraphicsRootSignature(sPip_[5].rootSignature.Get());
		break;
	}
}

void ParticleManager::DrawCommand()
{
	// プリミティブ形状の設定コマンド
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer_->GetView();
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	sCmdList_->SetGraphicsRootConstantBufferView(0, constBuffer_.get()->GetAddress());
	//SRVヒープの設定コマンド
	sCmdList_->SetDescriptorHeaps(1, texture_->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = texture_->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	sCmdList_->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	// 描画コマンド
	sCmdList_->DrawInstanced(static_cast<UINT>(std::distance(particles_.begin(),particles_.end())), 1, 0, 0);
}

void ParticleManager::BillboardUpdate(Camera* camera, Transform& transform)
{
	myMath::Matrix4 mTrans, mRot, mScale;
	myMath::Matrix4 mat = camera->GetMatView();

	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);

	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;

	transform.matWorld = mScale * mRot * mat * mTrans;
	transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();

	transform.Update();
	constBuffMap_ = transform.matWorld;
	constBuffer_->Update(&constBuffMap_);
}