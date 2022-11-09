#pragma once
#include "input.h"
#include "components.h"
#include <iostream>

class enemyManager
{
protected:
	
public:
	enemyManager();
	void onUpdate(timestep);
	glm::vec2 getMovementVec();
	glm::vec2 movementVec;
	float maxVel;
	float timestep;
};