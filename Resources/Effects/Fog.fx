#include "Common.fxh"

//Resources
cbuffer CBufferPerFrame
{
    float4 AmbientColour : AMBIENT = { 0.4, 0.4, 0.4, 1.0 };
    
    //The direction of a directional light.
    float3 LightDirection : DIRECTION = { -1.0f, -1.0f, 0.0f };
    
    float4 LightColour : COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    /*  */
    
    float3 FogColour = { 0.5f, 0.5f, 0.5f };
    
    float FogStart = { 1500.0f };
    
    float FogRange = { 4000.0f };
    
    float3 CameraPosition : CAMERAPOSITION;
};

cbuffer CBufferPerObject
{
    float4 SpecularColour : SPECULAR = { 1.0f, 1.0f, 1.0f, 1.0f };
	
    float SpecularPower : SPECULARPOWER = { 25.0f };
    
    /* */
    float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
    
    float4x4 World : WORLD;
};

//Utils
Texture2D ColourTexture;

SamplerState TrilinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

RasterizerState DisableCulling
{
    CullMode = NONE;
};

BlendState EnableAlphaBlending
{
    BlendEnable[0] = true;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

//Data Structures
struct VS_IN
{
    float4 objPos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

struct VS_OUT
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD0;
    float3 lightDir : TEXCOORD1;
    float3 viewDir : TEXCOORD2;
    float fogAmt : TEXCOORD3;
};

//Vertex Shader
VS_OUT vs_main(VS_IN input, uniform bool bFogEnabled)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.position = mul(input.objPos, WorldViewProjection);
    output.normal = normalize(mul(float4(input.normal, 0), World).xyz);
    output.texCoord = GetCorrectTexCoord(input.texCoord);
    
    output.lightDir = normalize(-LightDirection);
    
    /* */
    float3 worldPosition = mul(input.objPos, World).xyz;
    float3 viewDirection = (CameraPosition - worldPosition);
    output.viewDir = normalize(viewDirection);
    
    if (bFogEnabled)
    {
        output.fogAmt = GetFogAmount(viewDirection, FogStart, FogRange);
    }
    
    return output;
}

float4 ps_main(VS_OUT input, uniform bool bFogEnabled) : SV_Target
{
    float4 output = (float4) 0;
    
    float3 normal = normalize(input.normal);
    float3 viewDirection = normalize(input.viewDir);
    float4 colour = ColourTexture.Sample(TrilinearSampler, input.texCoord);
    float3 ambient = GetVectorColourContribution(AmbientColour, colour);
    
    LIGHT_CONTRIBUTION_DATA lightContributionData;
    lightContributionData.colour = colour;
    lightContributionData.lightDirection = float4(input.lightDir, 1);
    lightContributionData.normal = normal;
    lightContributionData.viewDirection = viewDirection;
    lightContributionData.specularColour = SpecularColour;
    lightContributionData.specularPower = SpecularPower;
    lightContributionData.lightColour = LightColour;
    
    float3 totalContribution = GetLightContribution(lightContributionData);
    
    output.rgb = ambient + totalContribution;
    output.a = colour.a;
    
    if (bFogEnabled)
    {
        output.rgb = lerp(output.rgb, FogColour, input.fogAmt);
    }
    
    return output;
}

technique11 main11
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vs_main(true)));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, ps_main(true)));
        
        SetRasterizerState(DisableCulling);
    }
}

technique11 FogEnabled
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vs_main(true)));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, ps_main(true)));
        
        SetRasterizerState(DisableCulling);
    }
}


technique11 FogDisabled
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vs_main(false)));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, ps_main(false)));
        SetBlendState(EnableAlphaBlending, (float4) 0, 0xFFFFFFFF);
        SetRasterizerState(DisableCulling);
    }
}