#include "components.h"
#include "input.h"
#include <iostream>

class SimpleController : public NativeScript
{
public:
	SimpleController(entt::entity& entity) : NativeScript(entity) {}
	void onCreate() override 
	{
		auto& rc = m_registry.get<RenderComponent>(m_entity);
		m_colour = rc.tint;


	};

	void onUpdate(float timestep) override 
	{


		auto& rc = m_registry.get<RenderComponent>(m_entity);
		rc.tint = m_colour;

		// Do some control
		auto& rb = m_registry.get<RigidBodyComponent>(m_entity);

		b2Vec2 DesVel(0.f, 0.f);

		float DesAnglVel = 0.f;

		//if (Input::isKeyPressed(GLFW_KEY_SPACE))
		//{
		//	// Jump
		//	rb.body->ApplyLinearImpulseToCenter(b2Vec2(0.f, 0.3f), true);
		//}

		if (Input::isKeyPressed(GLFW_KEY_W))
		{
			// Up
			// rb.body->ApplyLinearImpulseToCenter(b2Vec2(0.f, 0.2f), true);

			float _sin = sinf(rb.body->GetAngle());
			float _cos = cosf(rb.body->GetAngle());
			float x =  0.f;
			float y =  2.f;

			float xPrime = x * _cos - y * _sin;
			float yPrime = x * _sin + y * _cos;

			DesVel += b2Vec2(xPrime, yPrime);
		}
		if (Input::isKeyPressed(GLFW_KEY_A))
		{
			// Up
			//rb.body->ApplyLinearImpulseToCenter(b2Vec2(-0.2f, 0.0f), true);
			float _sin = sinf(rb.body->GetAngle());
			float _cos = cosf(rb.body->GetAngle());
			float x = -2.f;
			float y = 0.f;

			float xPrime = x * _cos - y * _sin;
			float yPrime = x * _sin + y * _cos;

			DesVel += b2Vec2(xPrime, yPrime);
		}if (Input::isKeyPressed(GLFW_KEY_S))
		{
			// Up
			//rb.body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -0.2f), true);
			float _sin = sinf(rb.body->GetAngle());
			float _cos = cosf(rb.body->GetAngle());
			float x = 0.f;
			float y = -2.f;

			float xPrime = x * _cos - y * _sin;
			float yPrime = x * _sin + y * _cos;

			DesVel += b2Vec2(xPrime, yPrime);
		}if (Input::isKeyPressed(GLFW_KEY_D))
		{
			// Up
			//rb.body->ApplyLinearImpulseToCenter(b2Vec2(0.2f, 0.f), true);
			float _sin = sinf(rb.body->GetAngle());
			float _cos = cosf(rb.body->GetAngle());
			float x = 2.f;
			float y = 0.f;

			float xPrime = x * _cos - y * _sin;
			float yPrime = x * _sin + y * _cos;

			DesVel += b2Vec2(xPrime, yPrime);
		}

		if (Input::isKeyPressed(GLFW_KEY_Q))
		{
			DesAnglVel = 2.5f;
		}
		if (Input::isKeyPressed(GLFW_KEY_E))
		{
			DesAnglVel = -2.5f;
		}

		b2Vec2 CurVel = rb.body->GetLinearVelocity();
		b2Vec2 DeltVel = DesVel - CurVel;

		b2Vec2 force(rb.body->GetMass() * b2Vec2(DeltVel.x / timestep, DeltVel.y / timestep));
		rb.body->ApplyForceToCenter(force, true);

		//Renderer::movePointLight(Renderer::playerLID, rb.body->GetPosition().x, rb.body->GetPosition().y);

		float CurAngVel = rb.body->GetAngularVelocity();
		float DeltaAngVel = DesAnglVel - CurAngVel;

		float angleForce(rb.body->GetInertia() * (DeltaAngVel / timestep));
		std::cout << "ang " << angleForce << "\n";
		rb.body->ApplyTorque(angleForce, true);
	};

	void onCollision(CollisionData& collisionData) override {
		std::cout << "hit\n";
	};
private:
	glm::vec4 m_colour = glm::vec4(1.f);
};