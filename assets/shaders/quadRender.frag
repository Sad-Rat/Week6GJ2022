#version 440 core
			
layout(location = 0) out vec4 colour;

uniform float aLightIntensity;
uniform vec3 aLightColour;

uniform vec2 pLightPos;

in vec2 texCoord;
in vec2 posWS;

uniform vec4 u_tint;
uniform sampler2D u_texData;

float pointLight();

void main()
{
	colour = texture(u_texData, texCoord) * u_tint * aLightIntensity * pointLight();
}

float pointLight()
{
	float dist = length(pLightPos - posWS);
	
	return 1 / dist;
}

