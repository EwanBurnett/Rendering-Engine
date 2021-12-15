#ifndef _COMMON_FXH
#define _COMMON_FXH

//Constants
#define FLIP_TEXTURE_Y 1

//Data Structures
struct POINT_LIGHT
{
    float3 position;
    float lightRadius;
    float4 colour;
};

struct SPOT_LIGHT
{
    float3 position;
    float4 colour;
    float3 lookAt;
    float radius;
    float innerAngle;
    float outerAngle;
};

struct DIRECTIONAL_LIGHT
{
    float3 direction;
    float4 colour;
};

struct LIGHT_CONTRIBUTION_DATA
{
    float4 colour;
    float3 normal;
    float3 viewDirection;
    float4 lightColour;
    float4 lightDirection;
    float4 specularColour;
    float specularPower;
};

//Utilities
//Ensure that the texture is correctly flipped on the Y axis, if true.
float2 GetCorrectTexCoord(float2 textureCoordinate)
{
#if FLIP_TEXTURE_Y
    return float2(textureCoordinate.x, 1.0 - textureCoordinate.y);
#else
		return textureCoordinate;
#endif
}

float GetFogAmount(float3 viewDirection, float fogStart, float fogRange)
{
    return (saturate((length(viewDirection) - fogStart) / (fogRange)));
}

float3 GetVectorColourContribution(float4 light, float3 colour)
{
	//Colour (.rgb) * intensity (.a)
    return light.rgb * light.a * colour;
}

float3 GetScalarColourContribution(float4 light, float colour)
{
	//Colour (.rgb) * intensity (.a)
    return light.rgb * light.a * colour;
}

float4 GetLightData(float3 lightPos, float3 worldPos, float lightRadius)
{
    float4 lightData = (float4) 0;
    float3 lightDirection = lightPos - worldPos;
    
    lightData.xyz = normalize(lightDirection);
    lightData.w = saturate(1.0f - length(lightDirection) / lightRadius);    //Attenuation
    
    return lightData;
    
}

float3 GetLightContribution(LIGHT_CONTRIBUTION_DATA input)
{
    float3 lightDirection = input.lightDirection.xyz;
    
    float n_dot_l = dot(input.normal, lightDirection);
    float3 halfVector = normalize(lightDirection + input.viewDirection);
    float n_dot_h = dot(input.normal, halfVector);
    
    float4 lightCoefficients = lit(n_dot_l, n_dot_h, input.specularPower);
    float3 diffuse = GetVectorColourContribution(input.lightColour, lightCoefficients.y * input.colour.rgb) * input.lightDirection.w;
    float3 specular = GetScalarColourContribution(input.specularColour, min(lightCoefficients.y, input.colour.w)) * input.lightDirection.w;
    
    return (diffuse + specular);
    
}
#endif
