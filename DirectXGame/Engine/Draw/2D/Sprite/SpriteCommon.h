#pragma once
#include"DrawCommon.h"
#include"Pipeline.h"
#include"DirectXBase.h"
#include <wrl.h>
#include <d3d12.h>
#include "TextureManager.h"
#include "ConstantBuffer.h"

class SpriteCommon
{
public:

	static Microsoft::WRL::ComPtr<ID3D12Device>sDevice_;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>sCmdList_;

	static Blob sBlob_;//�V�F�[�_�I�u�W�F�N�g

	static std::array<PipelineSet, 6> sPip_;//�p�C�v���C��

public:

	/// <summary>
	/// �ÓI����������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �p�C�v���C���ɐݒ��K�p
	/// </summary>
	/// <param name="mode"></param>
	static void BlendSet(BlendMode mode);

	/// <summary>
	/// �R�}���h���X�g���s
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="vbView"></param>
	/// <param name="ibView"></param>
	/// <param name="constBuff">�萔�o�b�t�@</param>
	static void DrawCommand(TextureData* textureData, D3D12_VERTEX_BUFFER_VIEW vbView, D3D12_INDEX_BUFFER_VIEW ibView, ConstantBuffer* constBuff);

private:

	static void LoadShader();
};