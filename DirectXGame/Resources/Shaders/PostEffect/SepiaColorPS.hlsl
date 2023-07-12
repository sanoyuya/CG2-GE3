#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float sepia = 0.1f;
    float3 grayScale = (texcolor.r * 0.299 + texcolor.g * 0.597 + texcolor.b * 0.114);
    return float4(grayScale.r + sepia, grayScale.g, grayScale.b - sepia, 1.0f);
}