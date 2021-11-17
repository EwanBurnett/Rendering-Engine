/*

% Hello World Shader!

keywords: material classic

date: 211016

*/

cbuffer CBufferPerObject
{
	float4x4 WorldViewProjection :  WORLDVIEWPROJECTION;
}

BlendState Default{
	AlphaToCoverageEnable = TRUE;

};

DepthStencilState EnableDepth{
	DepthEnable = TRUE;
    DepthWriteMask = ALL;
    DepthFunc = LESS_EQUAL;
};

RasterizerState DisableCulling
{
	FillMode = SOLID;
	CullMode = NONE;
	FrontCounterClockwise = FALSE;
};

RasterizerState CullBackFacing
{
	FillMode = SOLID;
	CullMode = BACK;
	FrontCounterClockwise = FALSE;
};

RasterizerState CullFrontFacing
{
	FillMode = SOLID;
	CullMode = FRONT;
	FrontCounterClockwise = FALSE;
};
//Struct for the Vertex Shader input
struct VS_IN
{
	float4 objPos : POSITION;
	float4 color : COLOR;
};

//Struct for the Vertex Shader Output
struct VS_OUT
{
	float4 pos : SV_Position;
	float4 color : COLOR;
};

VS_OUT vertex_shader(VS_IN IN)
{
	VS_OUT output = (VS_OUT)0;		//Initialize a new empty VS_OUT object

	output.pos = mul(IN.objPos, WorldViewProjection);
	output.color = IN.color;

	return output;
}

float4 pixel_shader(VS_OUT IN) : SV_Target
{
	return IN.color;
}

technique11 main11
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, pixel_shader()));

		//SetBlendState(Default, 0);
		//SetDepthStencilState(EnableDepth, 0);
		//SetRasterizerState(DisableCulling);
	}

}