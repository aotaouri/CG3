#include "Particle.hlsli"

struct Material
{
    float4 color;
    int enableLighting;
    float4x4 uvTransform;
};

struct DirectionalLight
{
    float4 color;
    float3 direction;
    float intensity;
};


cbuffer gmaterial : register(b0)
{
    Material gmaterial;
};


cbuffer gDirectionalLight : register(b1)
{
    DirectionalLight gDirectionalLight;
};

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), gmaterial.uvTransform);
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    if (gmaterial.enableLighting != 0)
    {
        float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        
        output.color.rgb = gmaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
        output.color.a = gmaterial.color.a * textureColor.a;
    }
    else
    {
        output.color.rgb = gmaterial.color.rgb * textureColor.rgb;
        output.color.a = gmaterial.color.a * textureColor.a;
    }
   
    if (textureColor.a == 0.0)
    {
        discard;
    }
    
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}