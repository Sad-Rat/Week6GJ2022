#pragma once
#include <entt/entt.hpp>
#include "components.h"
#include "input.h"
#include <iostream>

class AI : public NativeScript
{
public:
	AI(entt::entity& entity, entt::entity& playerEnt) : NativeScript(entity), m_player(playerEnt) {}
	void onCreate() override
	{
		auto& rc = m_registry.get<RenderComponent>(m_entity);
		m_isRegisteredForDeletion = false;
	};

	void onUpdate(float timestep) override
	{
		auto& myTransform = m_registry.get<TransformComponent>(m_entity);
		auto& playerTransform = m_registry.get<TransformComponent>(m_player);
		glm::vec2 dist = myTransform.position - playerTransform.position;
		float distSq = dist.x * dist.x + dist.y * dist.y;
		//float dot = b2Dot(b2Vec3(myTransform.position.x, myTransform.position.y, 0.0f), b2Vec3(playerTransform.position.x, playerTransform.position.y, 0.0f));

		auto& rb = m_registry.get<RigidBodyComponent>(m_entity);
		b2Vec2 DesVel(0.f, 0.f);

		float DesAnglVel = 0.f;

		if (m_state == States::patrol)
		{
			if (distSq < m_rangeSq)
			{
				m_state = States::attack;
			}


			std::cout << "patrol" << std::endl;
		}
		else if (m_state == States::attack)
		{
			if (distSq >= m_rangeSq)
			{
				m_state = States::patrol;
			}
			float theta = atan2(-dist.y, -dist.x);
			
			

			if (theta <= 1 && theta >= -1)
			{
				float _sin = sinf(rb.body->GetAngle());
				float _cos = cosf(rb.body->GetAngle());
				//float x =  0.f;
				//float y =  2.f;
				float x = 2.f;
				float y = 0.f;

				float xPrime = x * _cos - y * _sin;
				float yPrime = x * _sin + y * _cos;

				DesVel += b2Vec2(xPrime, yPrime);
			}
			else if (theta >= 1)
			{
				DesAnglVel = -2.5f;
			}
			else if (theta <= -1)
			{
				DesAnglVel = 2.5f;
			}


			std::cout << "attack " << theta << std::endl;
		}

		/*b2Vec2 CurVel = rb.body->GetLinearVelocity();
		b2Vec2 DeltVel = DesVel - CurVel;

		b2Vec2 force(rb.body->GetMass() * b2Vec2(DeltVel.x / timestep, DeltVel.y / timestep));
		rb.body->ApplyForceToCenter(force, true);

		float CurAngVel = rb.body->GetAngularVelocity();
		float DeltaAngVel = DesAnglVel - CurAngVel;

		float angleForce(rb.body->GetInertia() * (DeltaAngVel / timestep));
		
		rb.body->ApplyTorque(angleForce, true);*/

	};

	void onCollision(CollisionData& collisionData) override {
		m_isRegisteredForDeletion = true;
	};
private:
	float m_rangeSq = 100.f;
	enum class States{patrol, attack};
	States m_state = States::patrol;
	entt::entity m_player;
};