#include "Particle.hlsli"

struct Material
{
    float4 color;
    int enableLighting;
    float4x4 uvTransform;
};

struct TransformationMatrix
{
    float4x4 WVP;
    float4x4 World;
    
};

struct DirectionalLight
{
    float4 color;
    float3 direction;
    float intensity;
};

StructuredBuffer<TransformationMatrix> gTransformationMatrices : register(t0);

VertexShaderOutput main(vertexShaderInput input, uint instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    output.position = mul(input.position, gTransformationMatrices[instanceId].WVP);
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrices[instanceId].World));
    return output;
}