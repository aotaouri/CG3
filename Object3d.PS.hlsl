// Object3D.PS.hlsl

// C++側の rootParameters[0] (b0レジスタ) と対応
cbuffer gTriangleColor : register(b0)
{
    float4 gColor;
};

struct PSInput
{
    float4 position : SV_POSITION;
};

float4 main(PSInput input) : SV_TARGET
{
    // 定数バッファから送られてきた色をそのまま出力
    return gColor;
}