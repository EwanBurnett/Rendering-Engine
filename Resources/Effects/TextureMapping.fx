/*

% Description of my shader.
% Second line of description for my shader.

keywords: material classic

date: YYMMDD

*/

#define FLIP_TEXTURE_Y 1

cbuffer CBufferPerObject
{
	float4x4 WorldViewProj : WORLDVIEWPROJECTION < string UIWidget = "NONE"; >;
}

RasterizerState DisableCulling
{
	CullMode = NONE;
};

Texture2D ColorTexture < 
	string ResourceName = "default_color.dds";
	string UIName = "Color Texture";
	string ResourceType = "2D";
>;

SamplerState ColorSampler
{
	//Filter = MIN_MAG_MIP_LINEAR;
	//Filter = ANISOTROPIC;
	Filter = MIN_MAG_MIP_POINT;
	AddressU = WRAP;
	AddressV = WRAP;
};

//Structs
//Struct for the Vertex Shader input
struct VS_IN
{
	float4 objPos : POSITION;
	float2 texCoord : TEXCOORD;
};

//Struct for the Vertex Shader Output
struct VS_OUT
{
	float4 pos : SV_Position;
	float2 texCoord : TEXCOORD;
};

//Utils
//Ensure that the texture is correctly flipped on the Y axis, if true.
float2 GetCorrectTexCoord(float2 textureCoordinate)
{
	#if FLIP_TEXTURE_Y
		return float2(textureCoordinate.x, 1.0 - textureCoordinate.y);
	#else
		return textureCoordinate;
	#endif
}

//Vertex Shader
VS_OUT vs_main(VS_IN input)
{
	VS_OUT output = (VS_OUT) 0;
	
	output.pos = mul(input.objPos, WorldViewProj);
	
	output.texCoord = GetCorrectTexCoord(input.texCoord);
	
	return output;
}

//Pixel Shader
float4 ps_main(VS_OUT input) : SV_Target
{
	return ColorTexture.Sample(ColorSampler, input.texCoord);
}

//Tech11
technique11 main11
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, vs_main()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, ps_main()));
		SetRasterizerState(DisableCulling);
	}
}