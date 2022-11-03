#include "TextureManager.h"
#include"DirectXTex.h"

TextureManager* TextureManager::textureManager = nullptr;

void TextureManager::Initialize()
{
	HRESULT result;
	device = DirectX_::GetInstance()->GetDevice();
	size_t maxCount = 1024;

	//�f�X�N���v�^�����W�̐ݒ�
	dsvRange.NumDescriptors = 1;//��x�̕`��Ɏg���e�N�X�`���̐�
	dsvRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	dsvRange.BaseShaderRegister = 0;//���W�X�^�ԍ�
	dsvRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NumDescriptors = (UINT)maxCount;

	//�f�X�N���v�^�q�[�v�̐���
	result = device->CreateDescriptorHeap(&srvDesc, IID_PPV_ARGS(dsvHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//�q�[�v�ݒ�
	prop.Type = D3D12_HEAP_TYPE_CUSTOM;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
}

TextureData TextureManager::LoadTexture(const std::string& filePath)
{
	wchar_t wfilePath[256];
	HRESULT result;

	if (texCount > 1024)
	{
		assert(0);
	}

	TextureData tmp{};

	DirectX::TexMetadata metaData{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	MultiByteToWideChar(CP_ACP, 0, filePath.c_str(), -1, wfilePath, _countof(wfilePath));

	//WIC�e�N�X�`���̃��[�h
	result = DirectX::LoadFromWICFile(
		wfilePath,
		DirectX::WIC_FLAGS_NONE,
		&metaData, scratchImg);
	assert(SUCCEEDED(result));

	//�~�b�v�}�b�v����
	result = DirectX::GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metaData = scratchImg.GetMetadata();
	}

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metaData.format = DirectX::MakeSRGB(metaData.format);

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metaData.format;
	textureResourceDesc.Width = metaData.width;//��
	textureResourceDesc.Height = (UINT)metaData.height;
	textureResourceDesc.DepthOrArraySize = (UINT16)metaData.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//�e�N�X�`���o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(tmp.texBuff.ReleaseAndGetAddressOf()));

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metaData.mipLevels; i++)
	{
		//�~�b�v���x�����w�肵�ăC���[�W���擾
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = tmp.texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,//�S�̈�փR�s�[
			img->pixels,//���f�[�^�A�h���X
			(UINT)img->rowPitch,//1���C���T�C�Y
			(UINT)img->slicePitch);//1���T�C�Y
	}
	assert(SUCCEEDED(result));

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	tmp.gpuHandle = dsvHeap->GetGPUDescriptorHandleForHeapStart();
	tmp.srvHeap = dsvHeap;

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr += static_cast<UINT64>(texCount) * incrementSize;
	tmp.gpuHandle.ptr += static_cast<UINT64>(texCount) * incrementSize;

	//�V�F�[�_�[���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metaData.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metaData.mipLevels);

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(tmp.texBuff.Get(), &srvDesc, cpuHandle);

	tmp.width = metaData.width;
	tmp.height = metaData.height;

	texCount++;

	return tmp;
}

void TextureManager::Destroy()
{
	delete textureManager;
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}