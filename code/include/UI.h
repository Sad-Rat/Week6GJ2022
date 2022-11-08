#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "renderer.h"

class UI {
public:
	UI(float winWidth, float winHeight, std::shared_ptr<Texture> pWT);
	~UI();
	void onRender();
	inline float getWinWidth() { return w_width; }
	inline float getWinHeight() { return w_height; }
	inline void setWinWidth(float width) { w_width = width; }
	inline void setWinHeight(float height) { w_height = height; }
	inline float getHpRemaining() { return hpRemaining; }
	inline void setHPRemaining(float HP, float HPMax) { hpRemaining = HP / HPMax; }
private:
	std::shared_ptr<Texture> hpTexture;
	std::shared_ptr<Texture> plainWhiteTexture;
	std::shared_ptr<Texture> scoreTexture;
	std::shared_ptr<Texture> timerTexture;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	float w_width;
	float w_height;
	float hpRemaining;
};