#include"Sprite.hlsli"

VSOutput main(float4 pos : POSITION,float4 color : COLOR, float2 uv : TEXCOORD)
{
	VSOutput output;
	output.svpos = mul(mat, pos);
	output.uv = uv;
    output.color = color;
	return output;
}