#include "ParticleManager.h"

PosScaleColor ParticleManager::vertices_[vertexCount_];
Microsoft::WRL::ComPtr<ID3D12Device>ParticleManager::sDevice_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>ParticleManager::sCmdList_;
Blob ParticleManager::sBlob_;//�V�F�[�_�I�u�W�F�N�g
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
	//�������s�����p�[�e�B�N����S�폜
	particles_.remove_if([](OneParticle& x)
		{
			return x.flame >= x.num_flame;
		}
	);

	//�S�p�[�e�B�N���X�V
	for (std::forward_list<OneParticle>::iterator it = particles_.begin();
		it != particles_.end();
		it++)
	{
		//�o�߃t���[�������J�E���g
		it->flame++;
		//���x�ɉ����x�����Z
		it->velocity = it->velocity + it->accel;
		//���x�ɂ��ړ�
		it->position = it->position + it->velocity;

		//�i�s�x��0�`1�͈̔͂Ɋ��Z
		float f = (float)it->flame / it->num_flame;
		//�X�P�[���̐��`���
		it->scale = (it->e_scale - it->s_scale) * f;
		it->scale += it->s_scale;

		it->color.x -= 5.0f;
		it->color.y -= 5.0f;
		it->color.z -= 5.0f;
		it->color.w -= 5.0f;
	}

	//�萔�o�b�t�@�փf�[�^�]��
	PosScaleColor* vertMap = nullptr;
	vertMap = new PosScaleColor;

	//�p�[�e�B�N���̏���1�����f
	for (std::forward_list<OneParticle>::iterator it = particles_.begin();it != particles_.end();it++)
	{
		//���W
		vertMap->pos = it->position;
		//�X�P�[��
		vertMap->scale = it->scale;
		//�J���[
		vertMap->color = it->color;
		//���̒��_��
		vertMap++;
	}
	vertexBuffer_->Update(vertMap);

	BillboardUpdate(camera, transform);
}

void ParticleManager::Add(float life, myMath::Vector3 position, myMath::Vector3 velocity, myMath::Vector3 accel, float start_scale, float end_scale, myMath::Vector4 color)
{
	//���X�g�ɗv�f��ǉ�
	particles_.emplace_front();
	//�ǉ������v�f�̎Q��
	OneParticle& p = particles_.front();
	//�l�̃Z�b�g
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
	//�u�����h���[�h�ɑΉ�
	BlendSet(blendMode_);
	//�`��R�}���h
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
		//x,y,z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
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
	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_.vs = DrawCommon::ShaderCompile(L"Resources/Shaders/Particle/ParticleVS.hlsl", "main", "vs_5_0", sBlob_.vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	sBlob_.ps = DrawCommon::ShaderCompile(L"Resources/Shaders/Particle/ParticlePS.hlsl", "main", "ps_5_0", sBlob_.ps.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
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
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	sCmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer_->GetView();
	sCmdList_->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	sCmdList_->SetGraphicsRootConstantBufferView(0, constBuffer_.get()->GetAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	sCmdList_->SetDescriptorHeaps(1, texture_->srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = texture_->gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	sCmdList_->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	// �`��R�}���h
	sCmdList_->DrawInstanced(static_cast<UINT>(std::distance(particles_.begin(),particles_.end())), 1, 0, 0);
}

void ParticleManager::BillboardUpdate(Camera* camera, Transform& transform)
{
	myMath::Matrix4 mTrans, mRot, mScale;
	myMath::Matrix4 mat = camera->GetMatView();

	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
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