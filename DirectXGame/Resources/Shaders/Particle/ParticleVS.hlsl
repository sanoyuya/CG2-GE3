#include "Particle.hlsli"

VSOutput main(float3 pos : POSITION, float scale : SCALE, float4 color : COLOR)
{
    VSOutput output; // ピクセルシェーダーに渡す値
    output.pos = float4(pos, 1);
    output.scale = scale;
    output.color = color;
    return output;
}