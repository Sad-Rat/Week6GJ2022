#pragma once
#include "light.h"

class pointLight : public light
{
public:
	pointLight();
	void init(vec2, float, Shader*);
	virtual void render(int) override;
	virtual void render(Shader*, int) override;
	virtual void setShader() override;
	virtual void setColour() override;
	virtual vec3 getColour() override;
	virtual void setIntensity() override;
	virtual float getIntensity() override;
	void setPos(vec2 pos);


private:
	vec2 m_pos;

};