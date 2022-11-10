#include "pointlight.h"
#include <sstream>
#include <iostream>

pointLight::pointLight()
{

}

void pointLight::init(vec2 pos, float inten, Shader* shader)
{
	m_pos = pos;
	intensity = inten;
	m_shader = shader;
}

void pointLight::render(Shader* shader, int pos)
{
	shader->use();
	shader->uploadFloat2("pLightPos", m_pos);
}
void pointLight::render(int pos)
{
	std::string toSend;
	toSend = ("PointLightsPos[" + std::to_string(pos) + "]");
	m_shader->uploadFloat2(toSend.c_str(), m_pos);
	toSend = ("PointLightsInten[" + std::to_string(pos) + "]");
	m_shader->uploadFloat(toSend.c_str(), intensity);
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

void pointLight::setPos(glm::vec2 pos)
{
	m_pos = pos;
}