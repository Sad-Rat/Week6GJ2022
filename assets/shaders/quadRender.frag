#version 440 core
			
layout(location = 0) out vec4 colour;

uniform float aLightIntensity;
uniform vec3 aLightColour;

uniform vec2 pLightPos;

uniform vec2 PointLightsPos[1000];
uniform float PointLightsInten[1000];
uniform vec3 PointLightsColour[20];

in vec2 texCoord;
in vec2 posWS;

uniform vec4 u_tint;
uniform sampler2D u_texData;

float pointLight(vec2, float);

void main()
{
	float pLightMul = 0.0f;
	for (int i = 0; i < 1000; i++)
	{
		pLightMul += pointLight(PointLightsPos[i], PointLightsInten[i]);
	}
	
	colour = texture(u_texData, texCoord) * u_tint * (aLightIntensity + pLightMul);
	
	
}

float pointLight(vec2 pLightPos, float inten)
{
	if(pLightPos == vec2(0))
	{
		return 0;
	}
	
	float dist = length(pLightPos - posWS);
	
	
	
	float temp = (1 / (dist * dist)) / 0.5 * 0.1f;
	if (temp  < 0.05f)
	{
		
	}
	else if (temp < 0.5f)
	{
		temp += 0.1f;
	}
	
	return temp;
}

