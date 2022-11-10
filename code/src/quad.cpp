#include "quad.h"



Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents, float angle, bool degrees)
{
	Quad result;

	result.m_position = centre;
	result.m_halfExtents = halfExtents;
	result.m_angle = degrees ? glm::radians(angle) : angle;

	return result;
}

Quad Quad::createTopLeftExtents(const glm::vec2& topLeft, const glm::vec2& Extents)
{
	Quad result;

	result.m_position = topLeft + Extents * 0.5f;
	result.m_position.y -= Extents.y;
	result.m_halfExtents = Extents * 0.5f;
	result.m_angle = 0;

	return result;
}