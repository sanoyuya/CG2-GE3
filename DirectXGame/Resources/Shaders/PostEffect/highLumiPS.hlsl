#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float grayScale = texcolor.r * 0.299 + texcolor.g * 0.587 + texcolor.b * 0.114;
    float extract = smoothstep(0.6, 0.9, grayScale);
    float4 highLumi = texcolor * extract; //çÇãPìxíäèo
    
    return float4(highLumi.rgb, 1.0f);
}