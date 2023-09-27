cbuffer cbuff0 : register(b0)
{
    float power;
    float grayScalePower;
};

//頂点シェーダーからの出力構造体
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float2 uv : TECCOORD;
};

//ガウシアン関数
float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
    return exp(-(d * d) / (2 * sigma * sigma));
}