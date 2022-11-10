#pragma once
/* \file renderer.h*/
#pragma once

#include <glm/glm.hpp>
#include <array>
#include <memory>

#include "texture.h"
#include "shader.h"
#include "VertexArray.h"
#include "quad.h"

/*
class Quad
{
public:
	Quad() = default;
	static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents, float angle, bool degrees = true);
	static Quad createTopLeftExtents(const glm::vec2& topLeft, const glm::vec2& Extents);
private:
	glm::vec2 m_position;
	glm::vec2 m_halfExtents;
	float m_angle;
	friend class Renderer;
};
*/

class UIRenderer
{
public:
	// Init
	static void init();
	// Basic commands
	static void clearScreen();
	static void setClearColour(const glm::vec4& colour);
	static void enableStandardBlend();
	static void enableAdditiveBlend();
	static void disableBlend();
	static void enableDepthTest();
	static void disableDepthTest();
	// Draw command
	static void begin(const glm::mat4& view, const glm::mat4& projection);
	static void end();
	static void drawQuad(const Quad& quad, const Texture& texture, const glm::vec4& tint, const glm::vec2& offset = glm::vec2(0.f, 0.f), const glm::vec2& size = glm::vec2(1.f, 1.f));
	static void drawText(const Quad& quad, const char& text, const glm::vec4& tint);
private:
	struct RendererData
	{
		RendererData() {};
		glm::vec3 clearColour = glm::vec3(1.f);
		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> VAO;
	};

	static RendererData s_data;
};