cbuffer cbuff0 : register(b0)
{
    matrix world; //���[���h�s��
    matrix matWorld; //���[���h���W
    float3 cameraPos; //�J�������W
};

cbuffer cbuff1 : register(b1)
{
    float3 m_ambient : packoffset(c0); // �A���r�G���g�W��
    float3 m_diffuse : packoffset(c1); // �f�B�t���[�Y�W��
    float3 m_specular : packoffset(c2); // �X�y�L�����[�W��
    float m_alpha : packoffset(c2.w); // �A���t�@
}

cbuffer cbuff2 : register(b2)
{
    float4 color;
}

static const int DIRLIGHT_NUM = 3;

struct DirLight
{
    float3 lightv; //���C�g�̕����̒P�ʃx�N�g��
    float3 lightcolor; //���C�g�̐F(RGB)
    uint active;
};

static const int POINTLIGHT_NUM = 3;

struct PointLight
{
    float3 lightPos; //���C�g�̍��W
    float3 lightColor; //���C�g�̐F(RGB)
    float3 lightAtten; //���C�g�̋��������W��
    uint active;
};

//�X�|�b�g���C�g�̐�
static const int SPOTLIGHT_NUM = 3;

struct SpotLight
{
    float3 lightv; //���C�g�̌��������̋t�x�N�g��
    float3 lightPos; //���C�g���W
    float3 lightColor; //���C�g�̐F(RGB)
    float3 lightAtten; //���C�g���������W��
    float2 lightFactorAngleCos; //���C�g�����p�x�̃R�T�C��
    uint active;
};
 
static const int CIRCLESHADOW_NUM = 3;

struct CircleShadow
{
    float3 dir; //�������e�̋t�x�N�g��(�P�ʃx�N�g��)
    float3 casterPos; //�L���X�^�[���W
    float distanceCasterLight; //�L���X�^�[�ƃ��C�g�̋���
    float3 atten; //���������W��
    float2 factorAngleCos; //�����p�x�̃R�T�C��
    uint active;
};

cbuffer cbuff3 : register(b4)
{
    float3 ambientColor;
    DirLight dirLights[DIRLIGHT_NUM];
    PointLight pointLights[POINTLIGHT_NUM];
    SpotLight spotLights[SPOTLIGHT_NUM];
    CircleShadow circleShadows[CIRCLESHADOW_NUM];
}

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float4 worldpos : POSITION; //���[���h���W
    float3 normal : NORMAL; // �@���x�N�g��
    float2 uv : TEXCOORD; // uv�l
};