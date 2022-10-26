#include "HeadsUpDisplay.h"
HeadsUpDisplay::HeadsUpDisplay()
{

}
HeadsUpDisplay::HeadsUpDisplay(Font* font)
{
	mpFont = font;
}
HeadsUpDisplay::~HeadsUpDisplay()
{

}
void HeadsUpDisplay::updateScore()
{

}
void HeadsUpDisplay::drawHUD(GraphicsSystem* graphicsSystem,int score, float time, float frameRate)
{
	drawScore(graphicsSystem, score);
	drawTime(graphicsSystem, time);
	drawFPS(graphicsSystem, frameRate);
}
void HeadsUpDisplay::drawScore(GraphicsSystem* graphicsSystem,int score)
{
	Vector2D topLeft = Vector2D(0, 0);
	Color white = Color(255, 255, 255, 0);
	std::string scoreString = std::to_string(score);
	graphicsSystem->writeText(mpFont, topLeft, white, ("Current Score: " + scoreString));
}
void HeadsUpDisplay::drawTime(GraphicsSystem* graphicsSystem, float time)
{
	Vector2D topRight = Vector2D(500, 0);
	Color white = Color(255, 255, 255, 0);
	std::string timeString = std::to_string(time);
	graphicsSystem->writeText(mpFont, topRight, white, ("Time Elapsed: " + timeString));
}
void HeadsUpDisplay::drawFPS(GraphicsSystem* graphicsSystem, float frameRate)
{
	Vector2D bottomLeft = Vector2D(0, 560);
	Color white = Color(255, 255, 255, 0);
	std::string fpsString = std::to_string(frameRate);
	graphicsSystem->writeText(mpFont, bottomLeft, white, ("Frame Rate: " + fpsString));
}