#include "projectile.h"
#include "scene.h"
#include "scripts/simpleController.h"

projectile::projectile(glm::vec2 pos, glm::vec2 velocity, glm::vec2 size, float dmg, float orientation, std::shared_ptr<Texture> texture)
{
	auto &m_registry = Scene::getRegistry();

	m_projEnt = m_registry.create();

	m_registry.emplace<TransformComponent>(m_projEnt, size, pos, orientation); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_projEnt, texture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_projEnt, m_projEnt, RigidBodyType::dynamic); // Add a dyanmic rigid body
	PhysicsMaterial zeroRes;
	zeroRes.restitution = 0.f;
	m_registry.emplace<BoxColliderComponent>(m_projEnt, m_projEnt, zeroRes); // Add a box collider with 0 resistition
	//m_registry.emplace<NativeScriptComponent>(m_projEnt);
	//m_registry.get<NativeScriptComponent>(m_projEnt).create<SimpleController>(m_projEnt);

	

	auto& rb = m_registry.get<RigidBodyComponent>(m_projEnt);
	rb.body->ApplyLinearImpulseToCenter(b2Vec2(velocity.x, velocity.y), true);

}


