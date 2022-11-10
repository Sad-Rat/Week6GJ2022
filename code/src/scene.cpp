#include "scene.h"

#include "scripts/simpleController.h"
#include "scripts/camController.h"
#include "scripts/projectile.h"

entt::registry Scene::m_registry;
std::shared_ptr<b2World> Scene::m_physicsWorld = nullptr;

Scene::Scene(float winWidth, float winHeight)
{
	m_physicsWorld.reset(new b2World(b2Vec2(0.f, 0.f)));
	m_physicsWorld->SetContactListener(&m_listener);

	Renderer::setClearColour({ 1.f, 1.f, 1.f, 1.f });

	letterCubeTexture.reset(new Texture("../assets/textures/letterCube.png"));
	unsigned char whitePx[3] = { 255,255,255 };
	plainWhiteTexture.reset(new Texture(1, 1, 3, whitePx, 1));

	//m_texturedBlock = m_registry.create(); // Create the entity
	//m_registry.emplace<TransformComponent>(m_texturedBlock, glm::vec2(3.f, 2.f), glm::vec2(4.f, 0.5f), -5.f); // Add a transform to the block
	//m_registry.emplace<RenderComponent>(m_texturedBlock, letterCubeTexture, glm::vec4(1.f)); // Add a render component
	//m_registry.emplace<RigidBodyComponent>(m_texturedBlock, m_texturedBlock); // Add a static rigid body
	//m_registry.emplace<BoxColliderComponent>(m_texturedBlock, m_texturedBlock); // Add a box collider with standard physics

	m_fallingBlock = m_registry.create(); 
	m_registry.emplace<TransformComponent>(m_fallingBlock, glm::vec2(0.5f, 0.5f), glm::vec2(4.f, 7.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_fallingBlock, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_fallingBlock, m_fallingBlock, RigidBodyType::dynamic); // Add a dyanmic rigid body
	PhysicsMaterial zeroRes;
	zeroRes.restitution = 0.f;
	m_registry.emplace<BoxColliderComponent>(m_fallingBlock, m_fallingBlock, zeroRes); // Add a box collider with 0 resistition
	m_registry.emplace<NativeScriptComponent>(m_fallingBlock);
	m_registry.get<NativeScriptComponent>(m_fallingBlock).create<SimpleController>(m_fallingBlock);

	m_wall1 = m_registry.create();
	m_registry.emplace<TransformComponent>(m_wall1, glm::vec2(1.5f, 100.f), glm::vec2(100.f, 0.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_wall1, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_wall1, m_wall1, RigidBodyType::_static); // Add a dyanmic rigid body

	m_registry.emplace<BoxColliderComponent>(m_wall1, m_wall1, zeroRes); // Add a box collider with 0 resistition

	m_wall2 = m_registry.create();
	m_registry.emplace<TransformComponent>(m_wall2, glm::vec2(1.5f, 100.f), glm::vec2(-100.f, 0.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_wall2, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_wall2, m_wall2, RigidBodyType::_static); // Add a dyanmic rigid body

	m_registry.emplace<BoxColliderComponent>(m_wall2, m_wall2, zeroRes); // Add a box collider with 0 resistition

	m_wall3 = m_registry.create();
	m_registry.emplace<TransformComponent>(m_wall3, glm::vec2(100.f, 1.5f), glm::vec2(0.f, 100.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_wall3, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_wall3, m_wall3, RigidBodyType::_static); // Add a dyanmic rigid body
	
	m_registry.emplace<BoxColliderComponent>(m_wall3, m_wall3, zeroRes); // Add a box collider with 0 resistition

	m_wall4 = m_registry.create();
	m_registry.emplace<TransformComponent>(m_wall4, glm::vec2(100.f, 1.5f), glm::vec2(0.f, -100.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_wall4, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_wall4, m_wall4, RigidBodyType::_static); // Add a dyanmic rigid body

	m_registry.emplace<BoxColliderComponent>(m_wall4, m_wall4, zeroRes); // Add a box collider with 0 resistition

	m_wall5 = m_registry.create();
	m_registry.emplace<TransformComponent>(m_wall5, glm::vec2(0.2f, 1.5f), glm::vec2(0.f, 0.f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_wall5, plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_wall5, m_wall5, RigidBodyType::_static); // Add a dyanmic rigid body

	m_registry.emplace<BoxColliderComponent>(m_wall5, m_wall5, zeroRes); // Add a box collider with 0 resistition

	m_camera = m_registry.create();
	m_registry.emplace<TransformComponent>(m_camera, glm::vec2(5.12f,4.f), glm::vec2(5.12f, 4.f), 0.f); // Add a transform to the block
	m_registry.emplace<CameraComponent>(m_camera, m_camera);
	m_registry.emplace<CameraControllerComponent>(m_camera);
	m_registry.emplace<NativeScriptComponent>(m_camera);
	m_registry.get<NativeScriptComponent>(m_camera).create<CamController>(m_camera);

	m_enemy = m_registry.create();
	m_registry.emplace<TransformComponent>(m_enemy, glm::vec2(0.5f, 0.5f), glm::vec2(-4.f, 7.0f), 0.f); // Add a transform to the block
	m_registry.emplace<RenderComponent>(m_enemy, plainWhiteTexture, glm::vec4(0.f, 1.f, 0.f, 1.f)); // Add a render component
	m_registry.emplace<RigidBodyComponent>(m_enemy, m_enemy, RigidBodyType::dynamic); // Add a dyanmic rigid body

	m_registry.emplace<BoxColliderComponent>(m_enemy, m_enemy, zeroRes); // Add a box collider with 0 resistition
	//m_registry.emplace<NativeScriptComponent>(m_enemy);
	//m_registry.get<NativeScriptComponent>(m_enemy).create<SimpleController>(m_enemy);

	m_projectiles.reserve(10000);

	m_UI.reset(new UI(winWidth, winHeight, plainWhiteTexture));
}


void Scene::onUpdate(float timeStep)
{
	// Update any scripts
	auto& scriptView = m_registry.view<NativeScriptComponent>();
	{
		for (auto& entity : scriptView)
		{
			auto& script = m_registry.get<NativeScriptComponent>(entity);
			script.onUpdate(timeStep);
		}
	}

	// update the world
	m_physicsWorld->Step(timeStep, 5, 2);

	// update any transforms
	auto& rbView = m_registry.view<TransformComponent, RigidBodyComponent>();

	for (auto& entity : rbView)
	{
		auto& transform = m_registry.get<TransformComponent>(entity);
		auto& rigidBody = m_registry.get<RigidBodyComponent>(entity);

		if (rigidBody.bodyType != RigidBodyType::_static)
		{
			// Update transform
			auto& b2_pos = rigidBody.body->GetPosition();
			transform.position = glm::vec2(b2_pos.x, b2_pos.y);
			transform.angle = rigidBody.body->GetAngle();
		}
	}
	if (timepassed >= 0.f)
	{
		timepassed -= timeStep;
	}

	if (Input::isKeyPressed(GLFW_KEY_F) && timepassed < 0.f)
	{
		//auto& m_registry = Scene::getRegistry();
		timepassed = 1.f;
		m_projectiles.push_back(m_registry.create());

		auto& tc = m_registry.get<TransformComponent>(m_fallingBlock);
		glm::vec2 blockCenter = tc.position;
		glm::vec2 offset;
		offset.x = cos(tc.angle) * (tc.halfExtents.y + 0.22);
		offset.y = sin(tc.angle) * (tc.halfExtents.y + 0.22);
		m_registry.emplace<TransformComponent>(m_projectiles.back(), glm::vec2(0.1f,0.1f), blockCenter+offset, glm::degrees(tc.angle)); // Add a transform to the block
		m_registry.emplace<RenderComponent>(m_projectiles.back(), plainWhiteTexture, glm::vec4(1.f, 0.f, 0.f, 1.f)); // Add a render component
		m_registry.emplace<RigidBodyComponent>(m_projectiles.back(), m_projectiles.back(), RigidBodyType::dynamic); // Add a dyanmic rigid body
		PhysicsMaterial zeroRes;
		zeroRes.restitution = 0.f;
		m_registry.emplace<BoxColliderComponent>(m_projectiles.back(), m_projectiles.back(), zeroRes); // Add a box collider with 0 resistition
		m_registry.emplace<NativeScriptComponent>(m_projectiles.back());
		m_registry.get<NativeScriptComponent>(m_projectiles.back()).create<projectile>(m_projectiles.back());



		auto& rb = m_registry.get<RigidBodyComponent>(m_projectiles.back());
		rb.body->ApplyLinearImpulseToCenter(b2Vec2((cos(tc.angle) * 0.1f), (sin(tc.angle) * 0.1f)), true);
	}

	float thresh = 10000 * 10000;
	auto& camTC = m_registry.get<TransformComponent>(m_camera);
	for (auto it = m_projectiles.begin(); it != m_projectiles.end();)
	{
		auto entity = *it;
		auto& tc = m_registry.get<TransformComponent>(entity);
		auto& script = m_registry.get<NativeScriptComponent>(entity);
		glm::vec2 dist = tc.position - camTC.position;

		glm::vec2 distSq = dist * dist;

		if ((distSq.x + distSq.y) > thresh )
		{
			//out of range deletion
			auto& rb = m_registry.get<RigidBodyComponent>(entity);
			m_physicsWorld->DestroyBody(rb.body);
			m_registry.destroy(entity);
			it = m_projectiles.erase(it);
		}
		else if (script.isRegisteredForDeletion())
		{
			//contact deletion
			auto& rb = m_registry.get<RigidBodyComponent>(entity);
			m_physicsWorld->DestroyBody(rb.body);
			m_registry.destroy(entity);
			it = m_projectiles.erase(it);
		}
		else 
		{
			++it;
		}

		

	}
	
}

void Scene::onRender()
{
	auto& cam = m_registry.get<CameraComponent>(m_camera);
	Renderer::begin(cam.view, cam.proj);
	Renderer::clearScreen();

	auto& renderView = m_registry.view<TransformComponent, RenderComponent>();

	for (auto& entity : renderView)
	{
		auto& transform = m_registry.get<TransformComponent>(entity);
		auto& render = m_registry.get<RenderComponent>(entity);

		Renderer::drawQuad(Quad::createCentreHalfExtents(transform.position, transform.halfExtents, transform.angle, false), *render.texture, render.tint);
	}

	Renderer::end();

	m_UI->onRender();
}
