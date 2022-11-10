#pragma once
#include "components.h"
#include "input.h"
#include <iostream>

class AI : public NativeScript
{
public:
	AI(entt::entity& entity) : NativeScript(entity) {}
	void onCreate() override
	{
		m_isRegisteredForDeletion = false;
	};

	void onUpdate(float timestep) override
	{

	};

	void onCollision(CollisionData& collisionData) override {
		m_isRegisteredForDeletion = true;
	};
private:
};