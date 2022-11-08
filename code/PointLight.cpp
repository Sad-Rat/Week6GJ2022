#include "pointlight.h"

void pointLight::init(vec2 pos, float inten, Shader* shader)
{
	m_pos = pos;
	intensity = inten;
	m_shader = shader;
}

void pointLight::render(Shader* shader)
{

}
void pointLight::render()
{
	m_shader->use();
	m_shader->uploadFloat2("pLightPos", m_pos);
}
void pointLight::setColour()
{

}
vec3 pointLight::getColour()
{
	return vec3(0.0);
}
void pointLight::setIntensity()
{

}
float pointLight::getIntensity()
{
	return 0.0f;
}

void pointLight::setShader()
{

}