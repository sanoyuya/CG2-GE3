#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float totalWeight = 0.0f, _Sigma = 0.005f, StepWidth = 0.001f;
    float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);

    for (float py = -_Sigma * 2; py <= _Sigma * 2; py += StepWidth)
    {
        for (float px = -_Sigma * 2; px <= _Sigma * 2; px += StepWidth)
        {
            float2 pickUV = input.uv + float2(px, py);
            float weight = Gaussian(input.uv, pickUV, _Sigma);
            col += tex.Sample(smp, input.uv) * weight;
            totalWeight += weight;
        }
    }
    col.rgb = col.rgb / totalWeight;
    return float4(col.rgb, 1);
}