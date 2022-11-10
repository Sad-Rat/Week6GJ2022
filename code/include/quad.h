#pragma once
#include <glm/glm.hpp>

class Renderer;
class UIRenderer;

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
	friend class UIRenderer;
};
