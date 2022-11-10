#pragma once
#include "components.h"
#include "input.h"
#include <iostream>

class projectile : public NativeScript
{
public:
	projectile(entt::entity& entity) : NativeScript(entity) {}
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
