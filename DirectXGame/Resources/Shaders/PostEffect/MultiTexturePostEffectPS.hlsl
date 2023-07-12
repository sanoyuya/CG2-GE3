#include"PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);//1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 col = { 0.0f, 0.0f, 0.0f, 0.0f };
    float4 color = tex0.Sample(smp, input.uv);
    float4 colorTex0 = float4(1.0f - color.rgb, 1.0f);
    float4 colorTex1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    
    float shiftU = 1.0f / 1280.0f;
    float shiftV = 1.0f / 720.0f;
    int num = 0;
    
    [loop]
    for (float i = -3.0f; i <= 3.0f; i++)
    {
        [loop]
        for (float j = -3.0f; j <= 3.0f; j++)
        {
            float2 pickUV = input.uv + float2(shiftU * i, shiftV * j);
            pickUV = clamp(pickUV, 0.0f, 0.9999f);
            colorTex1 += tex1.Sample(smp, pickUV);
            num++;
        }
    }
    colorTex1 = float4(colorTex1.rgb / num, 1);
    
    col = colorTex0;
    if (fmod(input.uv.y,0.1f)<0.05f)
    {
        col = colorTex1;
    }
    
    return float4(col.rgb, 1);
}