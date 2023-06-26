#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0); 

float4 main(VSOutput input) : SV_TARGET
{
    float shiftU = 1.0f / 1280.0f;
    float shiftV = 1.0f / 720.0f;
    float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    //col += tex.Sample(smp, input.uv + float2(-shiftU, -shiftV));
    //col += tex.Sample(smp, input.uv + float2(0.0f, -shiftV));
    //col += tex.Sample(smp, input.uv + float2(shiftU, -shiftV));
    
    //col += tex.Sample(smp, input.uv + float2(-shiftU, 0.0f));
    //col += tex.Sample(smp, input.uv + float2(0.0f, 0.0f));
    //col += tex.Sample(smp, input.uv + float2(shiftU, 0.0f));
    
    //col += tex.Sample(smp, input.uv + float2(-shiftU, shiftV));
    //col += tex.Sample(smp, input.uv + float2(0.0f, shiftV));
    //col += tex.Sample(smp, input.uv + float2(shiftU, shiftV));
    
    //col /= 9.0f;
    //return float4(col.rgb, 1);
    
    int num = 0;
    
    for (float i = -power; i <= power; i++)
    {
        for (float j = -power; j <= power; j++)
        {
            col += tex.Sample(smp, input.uv + float2(shiftU * i, shiftV * j));
            num++;
        }
    }
    
    return float4(col.rgb / num, 1);
}