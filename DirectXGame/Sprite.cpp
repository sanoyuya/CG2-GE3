#include "Sprite.h"
#include <d3dcompiler.h>
#include"Camera.h"

Microsoft::WRL::ComPtr<ID3D12Device>Sprite::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>Sprite::cmdList;
myMath::Matrix4 Sprite::matProjection;
Blob Sprite::blob;//�V�F�[�_�I�u�W�F�N�g
std::array<PipelineSet, 6> Sprite::pip;

void Sprite::Initialize()
{
	device = DirectX_::GetInstance()->GetDevice();
	cmdList = DirectX_::GetInstance()->GetCommandList();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetHeight());

	myMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateSpritePipline(blob, (BlendMode)i, device.Get(), pip);
	}
}

void Sprite::SpriteInitialize()
{
	CreateVertexIndexBuffer();

	CreateConstBuff();
}

void Sprite::DrawSprite(TextureData& textureData, myMath::Vector2 position, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height) * isFlipY;

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{0.0f,1.0f},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{1.0f,0.0f},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{1.0f,1.0f},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//�C���f�b�N�X���R�s�[
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//�C���f�b�N�X���R�s�[
	}

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	BlendSet((BlendMode)blendMode);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteX(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width/ sheetsNum) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width / sheetsNum) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height) * isFlipY;

	if (nowNum + 1 > sheetsNum)
	{
		nowNum = 0;//0���ڂɖ߂�����
	}

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(float)nowNum / (float)sheetsNum,0.0f},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{(float)nowNum / (float)sheetsNum,1.0f},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{((float)nowNum + 1) / (float)sheetsNum,0.0f},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{((float)nowNum + 1) / (float)sheetsNum,1.0f},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//�C���f�b�N�X���R�s�[
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//�C���f�b�N�X���R�s�[
	}

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	BlendSet((BlendMode)blendMode);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteY(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height/ sheetsNum) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height / sheetsNum) * isFlipY;

	if (nowNum + 1 > sheetsNum)
	{
		nowNum = 0;//0���ڂɖ߂�����
	}

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,(float)nowNum / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{0.0f,((float)nowNum + 1) / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{1.0f,(float)nowNum / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{1.0f,((float)nowNum + 1) / (float)sheetsNum},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//�C���f�b�N�X���R�s�[
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//�C���f�b�N�X���R�s�[
	}

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	BlendSet((BlendMode)blendMode);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteXY(TextureData& textureData, myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width/ sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height/ sheetsNumY) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height / sheetsNumY) * isFlipY;

	uint16_t animationXYNum = sheetsNumX * sheetsNumY;//������(�����v)
	uint16_t x = nowNum % sheetsNumX;
	uint16_t y = nowNum / sheetsNumX;

	if (nowNum + 1 > animationXYNum)
	{
		nowNum = 0;//0���ڂɖ߂�����
	}

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(float)x / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{(float)x / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{((float)x + 1) / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{((float)x + 1) / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//�C���f�b�N�X���R�s�[
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//�C���f�b�N�X���R�s�[
	}

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	BlendSet((BlendMode)blendMode);

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.gpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::SetBlendMode(BlendMode mode)
{
	blendMode = int(mode);
}

void Sprite::CreateVertexIndexBuffer()
{
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^�T�C�Y����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * 4);

	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���_�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProp,//���\�[�X�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//���_�o�b�t�@�r���[�̍쐬
	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(PosUvColor);

	//�C���f�b�N�X�f�[�^�̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * 6);
	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�@
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(indexBuff.ReleaseAndGetAddressOf()));

	//�C���f�b�N�X�o�b�t�@�̃}�b�s���O
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	assert(SUCCEEDED(result));
}

void Sprite::CreateConstBuff()
{
	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(myMath::Matrix4) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//�萔�o�b�t�@�̃}�b�s���O
	result = constBuff->Map(0, nullptr, (void**)&constBuffMap);//�}�b�s���O
	assert(SUCCEEDED(result));
}

void Sprite::LoadShader()
{
	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	blob.vs = DrawCommon::ShaderCompile(L"Resources/shaders/SpriteVS.hlsl", "main", "vs_5_0", blob.vs.Get());
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	blob.ps = DrawCommon::ShaderCompile(L"Resources/shaders/SpritePS.hlsl", "main", "ps_5_0", blob.ps.Get());
}

void Sprite::Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation)
{
	myMath::Matrix4 mTrans, mRot, mScale, matWorld;
	//���s�ړ��s��
	mTrans.MakeTranslation({ position.x,position.y,0.0f });
	//��]�s��
	mRot.MakeRotation({ 0.0f,0.0f,rotation });
	//�X�P�[���s��
	mScale.MakeScaling({ scale.x,scale.y,1.0f });
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

	*constBuffMap = matWorld * matProjection;
}

void Sprite::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		cmdList->SetPipelineState(pip[0].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		cmdList->SetPipelineState(pip[1].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		cmdList->SetPipelineState(pip[2].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		cmdList->SetPipelineState(pip[3].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		cmdList->SetPipelineState(pip[4].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		cmdList->SetPipelineState(pip[5].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[5].rootSignature.Get());

		break;
	}
}