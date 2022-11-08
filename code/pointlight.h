#pragma once
#include "light.h"

class pointLight : public light
{
public:
	void init(vec2, float, Shader*);
	virtual void render() override;
	virtual void render(Shader*) override;
	virtual void setShader() override;
	virtual void setColour() override;
	virtual vec3 getColour() override;
	virtual void setIntensity() override;
	virtual float getIntensity() override;


private:
	vec2 m_pos;

};