#include "UI.h"
#include <string>

UI::UI(float winWidth, float winHeight, std::shared_ptr<Texture> pWT)
{
	hpTexture.reset(new Texture("../assets/textures/fontTest.png"));
	timerTexture.reset(new Texture("../assets/textures/timerTexture.png"));
	scoreTexture.reset(new Texture("../assets/textures/scoreTexture.png"));
	numberTexture.reset(new Texture("../assets/textures/numberTexture.png"));
	m_view = glm::mat4(1.0f);
	m_proj = glm::ortho(0.f, winWidth, 0.f, winHeight);
	plainWhiteTexture = pWT;
	setWinHeight(winHeight);
	setWinWidth(winWidth);
	hpRemaining = 0.9f;
	timeSec = 100;
	score = 2547;
}

UI::~UI()
{
}

void UI::onRender()
{
	UIRenderer::begin(m_view, m_proj);

	UIRenderer::enableStandardBlend();
	//UIRenderer::drawQuad(Quad::createCentreHalfExtents(glm::vec2(512, 400), glm::vec2(400, 400), 0, false), *hpTexture, glm::vec4(1.0f));
	UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(10, 100), glm::vec2(210, 70)), *hpTexture, glm::vec4(1.0f)); //hp background
	UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(15, 50), glm::vec2(200 * hpRemaining, 15)), *plainWhiteTexture, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); //hp bar
	UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(10, getWinHeight() - 10), glm::vec2(336, 70)), *timerTexture, glm::vec4(1.0f)); //timer background
	UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 346, getWinHeight() - 10), glm::vec2(336, 70)), *scoreTexture, glm::vec4(1.0f)); //score background

	std::string scoreString = std::to_string(getScore());

	for (int i = 0; i < scoreString.length(); i++) {
		switch (scoreString.at(i))
		{
		case '0':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(120.f/175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '1':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(0.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '2':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(30.f/175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '3':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(60.f/175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '4':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(90.f/175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '5':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(120.f/175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '6':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(0.f, 45.f/175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '7':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(30.f/175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '8':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(60.f/175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '9':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(getWinWidth() - 156 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(90.f/175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		default:
			break;
		}
	}


	int seconds = getTime() % 60;
	int minutes = (int)(getTime() / 60);

	std::string timeString = std::to_string(minutes);
	timeString +=':';
	timeString += std::to_string(seconds);



	for (int i = 0; i < timeString.length(); i++) {
		switch (timeString.at(i))
		{
		case '0':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(120.f / 175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '1':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(0.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '2':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(30.f / 175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '3':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(60.f / 175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '4':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(90.f / 175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '5':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(120.f / 175.f, 0.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '6':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(0.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '7':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(30.f / 175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '8':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(60.f / 175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case '9':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(90.f / 175.f, 45.f / 175.f), glm::vec2(30.f / 175.f, 45.f / 175.f));
			break;
		case ':':
			UIRenderer::drawQuad(Quad::createTopLeftExtents(glm::vec2(206 + (i * 30), getWinHeight() - 15), glm::vec2(26, 60)), *numberTexture, glm::vec4(1.0f), glm::vec2(0.f / 175.f, 90.f/ 175.f), glm::vec2(30.f/175.f, 45.f / 175.f));
			break;
		default:
			break;
		}
	}


	UIRenderer::disableBlend();

	UIRenderer::end();
}
