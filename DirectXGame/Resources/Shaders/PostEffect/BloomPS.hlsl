#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float grayScale = texcolor.r * 0.299 + texcolor.g * 0.587 + texcolor.b * 0.114;
    float extract = smoothstep(0.6, 0.9, grayScale);
    float4 highLumi = texcolor * extract;//çÇãPìxíäèo
    
    float totalWeight = 0.0f, _Sigma = power / 1000.0f + 0.0001f, StepWidth = 0.001f;
    float4 col = (0.0f, 0.0f, 0.0f, 0.0f);

    for (float py = -_Sigma * 2; py <= _Sigma * 2; py += StepWidth)
    {
        for (float px = -_Sigma * 2; px <= _Sigma * 2; px += StepWidth)
        {
            float2 pickUV = input.uv + float2(px, py);
            pickUV = clamp(pickUV, 0.0f, 0.9999f);
            float weight = Gaussian(input.uv, pickUV, _Sigma);
            col += (extract + tex.Sample(smp, pickUV)) * weight;
            totalWeight += weight;
        }
    }
    col.rgb = col.rgb / totalWeight;
    
    return float4(col.rgb, 1.0f);
}