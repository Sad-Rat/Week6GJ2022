#include "UI.h"

UI::UI(float winWidth, float winHeight, std::shared_ptr<Texture> pWT)
{
	hpTexture.reset(new Texture("../assets/textures/fontTest.png"));
	m_view = glm::mat4(1.0f);
	m_proj = glm::ortho(0.f, winWidth, 0.f, winHeight);
	plainWhiteTexture = pWT;
	setWinHeight(winHeight);
	setWinWidth(winWidth);
}

UI::~UI()
{
}

void UI::onRender()
{
	Renderer::begin(m_view, m_proj);

	Renderer::enableStandardBlend();
	//Renderer::drawQuad(Quad::createCentreHalfExtents(glm::vec2(512, 400), glm::vec2(400, 400), 0, false), *hpTexture, glm::vec4(1.0f));
	Renderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(10, 100), glm::vec2(420 * 0.5f, 140 * 0.5f)), *hpTexture, glm::vec4(1.0f));
	Renderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(15, 50), glm::vec2(400 * 0.5f, 30 * 0.5f)), *plainWhiteTexture, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Renderer::disableBlend();

	Renderer::end();
}
