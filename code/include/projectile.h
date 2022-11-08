#pragma once


#include "components.h" 

class projectile
{
protected:
	entt::entity m_projEnt;
	float m_projDmgVal;
	
	float m_projOrientation;
	glm::vec2 m_projVelocity;
	glm::vec2 m_projPos;
	glm::vec2 m_projSize; 
public:
	projectile(glm::vec2 pos, glm::vec2 velocity, glm::vec2 size, float dmg, float orientation, std::shared_ptr<Texture> texture);
	float getDamage();
	void setDamage(float dmg);
	glm::vec2 getProjectilePosition();
	void setProjectilePosition(glm::vec2 pis);
	void onUpdate(float timestep);
};
