#include "HeadsUpDisplay.h"
using namespace std;
HeadsUpDisplay::HeadsUpDisplay()
{
	mpTextData = new HudText;
}
HeadsUpDisplay::HeadsUpDisplay(Font* font)
{
	mpFont = font;
	mpTextData = new HudText;
}
HeadsUpDisplay::~HeadsUpDisplay()
{
	delete mpTextData;
	mpTextData = nullptr;
}
void HeadsUpDisplay::updateScore()
{

}
void HeadsUpDisplay::loadLanguage(std::string fileName)
{
	ifstream input;
	input.open(FILE_PATH + fileName);

	while (!input.eof()) {
		//record data
		string a;
		input >> a;

		if (a == "score")
		{
			string temp;
			getline(input, temp);
			mpTextData->mScore = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "time")
		{
			string temp;
			getline(input, temp);
			mpTextData->mTime = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "fps")
		{
			string temp;
			getline(input, temp);
			mpTextData->mFPS = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "start")
		{
			string temp;
			getline(input, temp);
			mpTextData->mStart = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "quit")
		{
			string temp;
			getline(input, temp);
			mpTextData->mQuit = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "settings")
		{
			string temp;
			getline(input, temp);
			mpTextData->mSettings = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "save")
		{
			string temp;
			getline(input, temp);
			mpTextData->mSave = temp;
		}
		else if (a == "load")
		{
			string temp;
			getline(input, temp);
			mpTextData->mLoad = temp;
		}
		else if (a == "e")
		{
			string temp;
			getline(input, temp);
			mpTextData->mEasy = temp;
		}
		else if (a == "m")
		{
			string temp;
			getline(input, temp);
			mpTextData->mMedium = temp;
		}
		else if (a == "h")
		{
			string temp;
			getline(input, temp);
			mpTextData->mHard = temp;
		}
		else if (a == "eng")
		{
			string temp;
			getline(input, temp);
			mpTextData->mEng = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "spa")
		{
			string temp;
			getline(input, temp);
			mpTextData->mSpa = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "fre")
		{
			string temp;
			getline(input, temp);
			mpTextData->mFre = temp;
		}
		else if (a == "aur")
		{
			string temp;
			getline(input, temp);
			mpTextData->mAure = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "death")
		{
			string temp;
			getline(input, temp);
			mpTextData->mDeath = temp;
			//mTextMap.insert(a, temp);
		}
		else if (a == "pause")
		{
			string temp;
			getline(input, temp);
			mpTextData->mPause = temp;
			//mTextMap.insert(a, temp);
		}
	}
}
void HeadsUpDisplay::setFont(Font* Font)
{
	mpFont = Font;
}
HudText* HeadsUpDisplay::getText()
{
	return mpTextData;
}
void HeadsUpDisplay::drawHUD(GraphicsSystem* graphicsSystem,int score, float time, float frameRate)
{
	drawScore(graphicsSystem, score);
	drawTime(graphicsSystem, time);
	drawFPS(graphicsSystem, frameRate);
}
void HeadsUpDisplay::drawScore(GraphicsSystem* graphicsSystem,int score)
{
	Vector2D topLeft = Vector2D(150, 20);
	Color white = Color(255, 255, 255, 0);
	std::string scoreString = std::to_string(score);
	graphicsSystem->writeText(mpFont, topLeft, white, (getText()->mScore + scoreString));
}
void HeadsUpDisplay::drawTime(GraphicsSystem* graphicsSystem, float time)
{
	Vector2D topRight = Vector2D(600, 20);
	Color white = Color(255, 255, 255, 0);
	std::string timeString = std::to_string(time);
	graphicsSystem->writeText(mpFont, topRight, white, (getText()->mTime + timeString));
}
void HeadsUpDisplay::drawFPS(GraphicsSystem* graphicsSystem, float frameRate)
{
	Vector2D bottomLeft = Vector2D(200, 580);
	Color white = Color(255, 255, 255, 0);
	std::string fpsString = std::to_string(frameRate);
	graphicsSystem->writeText(mpFont, bottomLeft, white, (getText()->mFPS + fpsString));
}