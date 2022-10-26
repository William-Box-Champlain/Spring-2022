#pragma once
#include <Trackable.h>
#include "Font.h"
#include <Vector2D.h>
#include "Color.h"
#include "GraphicsSystem.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

const std::string FILE_PATH = "..\\..\\Box and Pottmeyer\\Box and Pottmeyer Final\\Data\\";

struct HudText
{	
	std::string mScore = "";
	std::string mTime = "";
	std::string mFPS = "";
	std::string mStart = "";
	std::string mQuit = "";
	std::string mSettings = "";
	std::string mSave = "";
	std::string mLoad = "";
	std::string mEasy = "";
	std::string mMedium = "";
	std::string mHard = "";
	std::string mEng = "";
	std::string mSpa = "";
	std::string mFre = "";
	std::string mAure = "";
	std::string mDeath = "";
	std::string mPause = "";
};

class HeadsUpDisplay:public Trackable
{
public:
	HeadsUpDisplay();
	HeadsUpDisplay(Font* Font);
	~HeadsUpDisplay();
	void updateScore();
	void drawHUD(GraphicsSystem* graphicsSystem,int score,float time,float frameRate);
	void loadLanguage(std::string fileName);
	void setFont(Font* Font);
	HudText* getText();
private:
	void drawScore(GraphicsSystem* graphicsSystem,int score);
	void drawTime(GraphicsSystem* graphicsSystem,float time);
	void drawFPS(GraphicsSystem* graphicsSystem,float frameRate);
	Font* mpFont;
	HudText* mpTextData;
	//std::map<std::string, std::string> mTextMap;
};