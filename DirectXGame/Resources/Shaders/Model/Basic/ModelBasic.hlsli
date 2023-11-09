cbuffer cbuff0 : register(b0)
{
    matrix world; //���[���h�s��
    matrix matWorld; //���[���h���W
    float3 cameraPos;//�J�������W
};

cbuffer cbuff1 : register(b1)
{
    float3 m_ambient : packoffset(c0); //�A���r�G���g�W��
    float3 m_diffuse : packoffset(c1); //�f�B�t���[�Y�W��
    float3 m_specular : packoffset(c2); //�X�y�L�����[�W��
    float m_alpha : packoffset(c2.w); //�A���t�@
};

cbuffer cbuff2 : register(b2)
{
    float4 color; //�J���[
    float2 tiling; //�^�C�����O��
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float3 normal : NORMAL; // �@��
    float2 uv : TEXCOORD; // uv�l
};