struct PixelShaderInput
{
    float4 Normal    : NORMAL;
};

float4 main(PixelShaderInput IN) : SV_Target
{
    return IN.Normal;
}