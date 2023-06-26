#include"PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float _ShiftWidth = 0.005f;
    float _ShiftNum = 3.0f;

    float4 col = float4(0, 0, 0, 0);
    float num = 0;
    
    for (float py = -_ShiftNum / 2; py <= _ShiftNum / 2; py++)
    {
        for (float px = -_ShiftNum / 2; px <= _ShiftNum / 2; px++)
        {
            col += tex.Sample(smp, input.uv + float2(px, py) * _ShiftWidth);
            num++;
        }
    }
    col.rgb /= num;
    return float4(col.rgb, 1);
}