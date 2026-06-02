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
    output.position = input.position;
    return output;
}
