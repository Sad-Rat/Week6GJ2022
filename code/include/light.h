#pragma once
#include "shader.h"

using namespace glm;

class light
{
public:
	light();
	virtual void render();
	virtual void render(Shader*) = 0;
	virtual void setShader() = 0;
	virtual void setColour() = 0;
	virtual vec3 getColour() = 0;
	virtual void setIntensity() = 0;
	virtual float getIntensity() = 0;

protected:
	vec3 colour;
	float intensity;
	Shader* m_shader;
	
};