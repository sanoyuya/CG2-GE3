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

//�p�[�e�B�N��1��
struct OneParticle
{
	//���W
	myMath::Vector3 position = {};
	//���x
	myMath::Vector3 velocity = {};
	//�����x
	myMath::Vector3 accel = {};
	//���݃t���[��
	float flame = 0;
	//�I���t���[��
	float num_flame = 0;
	//�X�P�[��
	float scale = 1.0f;
	//�����l
	float s_scale = 1.0f;
	//�ŏI�l
	float e_scale = 0.0f;
	//�J���[
	myMath::Vector4 color = {};
};

class ParticleManager
{
private:

	static Microsoft::WRL::ComPtr<ID3D12Device>sDevice_;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>sCmdList_;

	std::forward_list<OneParticle>particles_; //���_��
	static const uint32_t vertexCount_ = 1024; //���_��
	//���_�f�[�^�z��
	static PosScaleColor vertices_[vertexCount_];

	HRESULT result_ = S_FALSE;
	char PADING_[4] = {};

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//���_�}�b�v
	PosUvColor* vertMap_ = {};

	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffer_ = {};

	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4 constBuffMap_ = {};

	TextureData* texture_ = {};

	BlendMode blendMode_ = BlendMode::Alpha;//�����l����������
	static Blob sBlob_;//�V�F�[�_�I�u�W�F�N�g
	static std::array<PipelineSet, 6> sPip_;//�p�C�v���C��

public:

	ParticleManager();
	~ParticleManager();

	static void StaticInitialize();

	void Initialize(uint32_t handle);

	void Update(Camera* camera, Transform& transform);

	void Add(float life, myMath::Vector3 position, myMath::Vector3 velocity, myMath::Vector3 accel, float start_scale, float end_scale, myMath::Vector4 color);
	
	void Draw();

	uint32_t LoadTexture(const std::string& filePath);

private:

	void CreateBuff();

	static void LoadShader();

	static void CreatePipline();

	void BlendSet(BlendMode mode);

	void DrawCommand();

	void BillboardUpdate(Camera* camera, Transform& transform);
};