#version 440 core
			
layout(location = 0) out vec4 colour;

uniform float aLightIntensity;
uniform vec3 aLightColour;

uniform vec2 pLightPos;

uniform vec2 PointLightsPos[20];
uniform float PointLightsInten[20];
uniform vec3 PointLightsColour[20];

in vec2 texCoord;
in vec2 posWS;

uniform vec4 u_tint;
uniform sampler2D u_texData;

float pointLight(vec2);

void main()
{
	float pLightMul = 0.0f;
	for (int i = 0; i < 19; i++)
	{
		pLightMul += pointLight(PointLightsPos[i]);
	}
	
	colour = texture(u_texData, texCoord) * u_tint * aLightIntensity * pLightMul;
	
	
}

float pointLight(vec2 pLightPos)
{
	if(pLightPos == vec2(0))
	{
		return 0;
	}
	
	float dist = length(pLightPos - posWS);
	
	return 1 / dist;
}

