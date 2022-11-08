#pragma once
#include "light.h"

class AmbientLight : public light
{
public:
	virtual void render() override;
	virtual void render(Shader*) override;
	virtual void setColour() override;
	virtual vec3 getColour() override;
	virtual void setIntensity() override;
	virtual float getIntensity() override;

private:

};