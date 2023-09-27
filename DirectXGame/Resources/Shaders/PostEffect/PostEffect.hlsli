cbuffer cbuff0 : register(b0)
{
    float power;
    float grayScalePower;
};

//���_�V�F�[�_�[����̏o�͍\����
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float2 uv : TECCOORD;
};

//�K�E�V�A���֐�
float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
    return exp(-(d * d) / (2 * sigma * sigma));
}