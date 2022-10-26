#pragma once
#include <Trackable.h>
#include "Font.h"
#include <Vector2D.h>
#include "Color.h"
#include "GraphicsSystem.h"
#include <string>
class HeadsUpDisplay:public Trackable
{
public:
	HeadsUpDisplay();
	HeadsUpDisplay(Font* Font);
	~HeadsUpDisplay();
	void updateScore();
	void drawHUD(GraphicsSystem* graphicsSystem,int score,float time,float frameRate);
private:
	void drawScore(GraphicsSystem* graphicsSystem,int score);
	void drawTime(GraphicsSystem* graphicsSystem,float time);
	void drawFPS(GraphicsSystem* graphicsSystem,float frameRate);
	Font* mpFont;
};