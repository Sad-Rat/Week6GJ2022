#pragma once

#include <entt/entt.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <box2d/box2d.h>

#include "UI.h"
#include "texture.h"
#include "renderer.h"
#include "components.h"
#include "ambientlight.h"

class Scene
{
public:
	Scene(float winWidth, float winHeight);
	void onUpdate(float timeStep);
	void onRender();
	static entt::registry& getRegistry() { return m_registry; }
	static b2World* getWorld() { return m_physicsWorld.get(); }
private:
	static entt::registry m_registry; //!< Entities stored in the registry - everything goes through this!
	static std::shared_ptr<b2World> m_physicsWorld;
	std::shared_ptr<UI> m_UI;
	CollisionListener m_listener;

	// Some entities, thse could also go in a vector or array
	entt::entity m_camera; 
	entt::entity m_texturedBlock;
	entt::entity m_fallingBlock;
	entt::entity m_wall1;
	entt::entity m_wall2;
	entt::entity m_wall3;
	entt::entity m_wall4;
	entt::entity m_wall5;
	entt::entity m_enemy;
	std::vector<entt::entity> m_projectiles;

	float timepassed = -1.f;

	// Some textures
	std::shared_ptr<Texture> plainWhiteTexture;
	std::shared_ptr<Texture> letterCubeTexture;

	AmbientLight* aLight;
};