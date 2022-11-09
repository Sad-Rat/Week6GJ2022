#pragma once


#include "components.h" 

class projectile
{
protected:
	entt::entity m_projEnt;

public:
	projectile(glm::vec2 pos, glm::vec2 velocity, glm::vec2 size, float dmg, float orientation, std::shared_ptr<Texture> texture);
};
