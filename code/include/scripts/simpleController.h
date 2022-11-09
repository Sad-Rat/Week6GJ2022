#include "components.h"
#include "input.h"
#include "projectile.h"
#include <iostream>

class SimpleController : public NativeScript
{
public:
	SimpleController(entt::entity& entity) : NativeScript(entity) {}
	void onCreate() override 
	{
		auto& rc = m_registry.get<RenderComponent>(m_entity);
		m_colour = rc.tint;
		unsigned char whitePx[3] = { 255,255,255 };
		plainWhiteTexture.reset(new Texture(1, 1, 3, whitePx, 1));
	};

	void onUpdate(float timestep) override 
	{
		// Change colour
		m_colour += glm::vec4(timestep, timestep * 0.5f, timestep * 0.25f, 0.f);
		if (m_colour.x > 0.8f) m_colour.x -= 1.f;
		if (m_colour.y > 0.8f) m_colour.y -= 1.f;
		if (m_colour.z > 0.8f) m_colour.z -= 1.f;

		timePass += timestep;

		auto& rc = m_registry.get<RenderComponent>(m_entity);
		rc.tint = m_colour;

		// Do some control
		auto& rb = m_registry.get<RigidBodyComponent>(m_entity);

		if (Input::isKeyPressed(GLFW_KEY_SPACE))
		{
			// Jump
			rb.body->ApplyLinearImpulseToCenter(b2Vec2(0.f, 0.3f), true);
		}
		if (Input::isKeyPressed(GLFW_KEY_S))
		{
			if (timePass >= 1) 
			{
				timePass = 0.f;
				//projectile proj1(glm::vec2(5.0f, 5.0f), glm::vec2(7.0f, 7.0f), glm::vec2(0.2f, 0.2f), 5.f, 0.f, plainWhiteTexture);



			}
			
		}
		
	};

	void onCollision(CollisionData& collisionData) override {
		std::cout << "hit\n";
	};
private:
	glm::vec4 m_colour = glm::vec4(1.f);
	std::shared_ptr<Texture> plainWhiteTexture;
	float timePass = 0.f;
};