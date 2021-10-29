struct VertexPosColor
{
    float3 Position : POSITION;
    float3 Normal   : NORMAL;
};

struct ModelViewProjection
{
    matrix MVP;
};

ConstantBuffer<ModelViewProjection> ModelViewProjectionCB : register(b0);

struct VertexShaderOutput
{
    float4 Normal   : NORMAL;
    float4 Position : SV_Position;
};



VertexShaderOutput main(VertexPosColor IN)
{
    VertexShaderOutput OUT;

    OUT.Position = mul(ModelViewProjectionCB.MVP, float4(IN.Position, 1.0f));
    OUT.Normal = float4(IN.Normal, 1.0f);

    return OUT;
}