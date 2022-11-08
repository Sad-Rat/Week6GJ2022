#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "renderer.h"

class UI {
public:
	UI(float winWidth, float winHeight, std::shared_ptr<Texture> pWT);
	~UI();
	void onRender();
private:
	std::shared_ptr<Texture> hpTexture;
	std::shared_ptr<Texture> plainWhiteTexture;
	glm::mat4 m_view;
	glm::mat4 m_proj;
};