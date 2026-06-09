struct TransformationMatrix
{
    float32_t4x4 WVP;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

struct VertexShaderOutput
{
    float32_t4 position : SV_Position;
};

struct vertexShaderInput
{
    float32_t4 position : POSITION0;
};

VertexShaderOutput main(vertexShaderInput input)
{
    VertexShaderOutput output;
    output.position = mul(input.position, gTransformationMatrix.WVP);
    return output;
}
