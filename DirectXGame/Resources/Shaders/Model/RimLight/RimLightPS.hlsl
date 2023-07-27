#include"RimLight.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    //�e�N�X�`���}�b�s���O
    float4 texcolor = tex.Sample(smp, input.uv);

    //����x
    const float shininess = 4.0f;
    //���_����n�_�ւ̕����x�N�g��
    float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
    //�����ˌ�
    float3 ambient = m_ambient;
    //�V�F�[�f�B���O�ɂ��F
    float4 shaderColor = float4(ambientColor * ambient * texcolor.rgb * color.rgb, color.a);
    
    //���s����
    [loop]
    for (int i = 0; i < DIRLIGHT_NUM; i++)
    {
        if (dirLights[i].active)
        {
            //���C�g�Ɍ������x�N�g���Ɩ@���̓���
            float3 dotLightNormal = dot(dirLights[i].lightv, input.normal);
            //���ˌ��x�N�g��
            float3 reflect = normalize(-dirLights[i].lightv + 2 * dotLightNormal * input.normal);
             //�g�U���ˌ�
            float3 diffuse = smoothstep(0.45, 0.5, dotLightNormal * m_diffuse);
            //���ʔ��ˌ�
            float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
    
            //�S�ĉ��Z����
            shaderColor.rgb = (diffuse + specular) * dirLights[i].lightcolor;
        }
    }
    
    //�_����
    [loop]
    for (i = 0; i < POINTLIGHT_NUM; i++)
    {
        if (pointLights[i].active)
        {
            //���C�g�ւ̃x�N�g��
            float3 lightv = pointLights[i].lightPos - input.worldpos.xyz;
            //�x�N�g���̒���
            float d = length(lightv);
            //���K�����A�P�ʃx�N�g���ɂ���
            lightv = normalize(lightv);
            //���������W��
            float atten = 1.0f / (pointLights[i].lightAtten.x + pointLights[i].lightAtten.y * d + pointLights[i].lightAtten.z * d * d);
            //���C�g�Ɍ������x�N�g���Ɩ@���̓���
            float3 dotLightNormal = dot(lightv, input.normal);
            //���ˌ��x�N�g��
            float3 reflect = -lightv + 2 * dotLightNormal * input.normal;
            //�g�U���ˌ�
            float3 diffuse = smoothstep(0.45, 0.5, saturate(dot(normalize(input.normal), lightv))) * texcolor.rgb * color.rgb * pointLights[i].lightColor;
            //���ʔ��ˌ�
            float3 specular = smoothstep(0.45, 0.5, pow(saturate(dot(reflect, eyedir)), shininess * m_diffuse)) * m_specular * pointLights[i].lightColor;
            
            float rim = 1 - step(0.3, dot(lightv, input.normal));
            
            //�S�ĉ��Z����
            shaderColor.rgb += atten * saturate(rim + diffuse + specular);
        }
    }
    
    //�X�|�b�g���C�g
    [loop]
    for (i = 0; i < SPOTLIGHT_NUM; i++)
    {
        if (spotLights[i].active)
        {
            //���C�g�ւ̕����x�N�g��
            float3 lightv = spotLights[i].lightPos - input.worldpos.xyz;
            float d = length(lightv);
            lightv = normalize(lightv);
            //���������W��
            float3 atten = saturate(1.0f / (spotLights[i].lightAtten + spotLights[i].lightAtten.y * d + spotLights[i].lightAtten.z * d * d));
            //�p�x����
            float cos = dot(lightv, spotLights[i].lightv);
            //�����J�n�p�x����A�����I���p�x�ɂ����Č���
            //�����J�n�p�x�̓���1�{ �����I���p�x�̊O����0�{�̋P�x
            float3 angleAtten = smoothstep(spotLights[i].lightFactorAngleCos.y, spotLights[i].lightFactorAngleCos.x, cos);
            //�p�x��������Z
            atten *= angleAtten;
            //���C�g�Ɍ������x�N�g���Ɩ@���̓���
            float3 dotLightNormal = dot(lightv, input.normal);
            //���ˌ��x�N�g��
            float3 reflect = -lightv + 2 * dotLightNormal * input.normal;
            //�g�U���ˌ�
            float3 diffuse = smoothstep(0.45, 0.5, saturate(dot(normalize(input.normal), lightv))) * texcolor.rgb * color.rgb * spotLights[i].lightColor;
            //���ʔ��ˌ�
            float3 specular = smoothstep(0.45, 0.5, pow(saturate(dot(reflect, eyedir)), shininess * m_diffuse)) * m_specular * spotLights[i].lightColor;
            
            float rim = 1 - step(0.3, dot(lightv, input.normal));
            
            //�S�ĉ��Z����
            shaderColor.rgb += atten * (rim + diffuse + specular) * spotLights[i].lightColor;
        }
    }
    
    //�ۉe
    [loop]
    for (i = 0; i < CIRCLESHADOW_NUM; i++)
    {
        if (circleShadows[i].active)
        {
            //�I�u�W�F�N�g�\�ʂ���L���X�^�[�ւ̃x�N�g��
            float3 casterv = circleShadows[i].casterPos - input.worldpos.xyz;
            //���e�����ł̋���
            float d = dot(casterv, circleShadows[i].dir);
            //���������W��
            float atten = saturate(1.0f / (circleShadows[i].atten.x + circleShadows[i].atten.y * d + circleShadows[i].atten.z * d * d));
            //�������}�C�i�X�Ȃ�0�ɂ���
            atten *= step(0, d);
            //���z���C�g�̍��W
            float3 lightPos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
            //�I�u�W�F�N�g�\�ʂ��烉�C�g�ւ̃x�N�g��(�P�ʃx�N�g��)
            float3 lightv = normalize(lightPos - input.worldpos.xyz);
            //�p�x����
            float cos = dot(lightv, circleShadows[i].dir);
            //�����J�n�p�x����A�����I���p�x�ɂ����Č���
            //�����J�n�p�x�̓�����1�{ �����I���p�x�̊O����0�{�̋P�x
            float angleAtten = smoothstep(circleShadows[i].factorAngleCos.y, circleShadows[i].factorAngleCos[i].x, cos);
            //�p�x��������Z
            atten *= angleAtten;
            
            //�S�Ă����Z����
            shaderColor.rgb -= atten;
        }
    }

    //�V�F�[�f�B���O�ɂ��F�ŕ`��
    return shaderColor;
}