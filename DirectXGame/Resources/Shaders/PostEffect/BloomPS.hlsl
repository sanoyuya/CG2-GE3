#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
Texture2D<float4> tex2 : register(t1);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float grayScale = texcolor.r * 0.299 + texcolor.g * 0.587 + texcolor.b * 0.114;
    float extract = smoothstep(0.6, 0.9, grayScale);
    //float4 highLumi = texcolor * extract; //高輝度抽出
    
    float totalWeight = 0.0f, _Sigma = 0.005f, StepWidth = 0.001f;
    float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);

    [loop]
    for (float py = -_Sigma * 2; py <= _Sigma * 2; py += StepWidth)
    {
        [loop]
        for (float px = -_Sigma * 2; px <= _Sigma * 2; px += StepWidth)
        {
            float2 pickUV = input.uv + float2(px, py);
            pickUV = clamp(pickUV, 0.0f, 0.9999f);
            float weight = Gaussian(input.uv, pickUV, _Sigma);
            float4 texcolor = tex.Sample(smp, pickUV);
            col += texcolor * weight;
            totalWeight += weight;
        }
    }
    col.rgb = col.rgb / totalWeight;
    float4 highLumi = col * extract; //高輝度抽出
    
    return float4(highLumi.rgb, 1.0f) + col;
}