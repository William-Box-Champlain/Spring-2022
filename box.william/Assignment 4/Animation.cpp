#include "Animation.h"
Animation::Animation()
{
	mFramesPerSecond = 0;
	mMilliSecondsBetweenFrames = 0;
	mCurrentFrame = 0;
	mShouldLoop = false;
}
Animation::Animation(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop)
{
	addMultipleSprites(spriteSheet, columnsAndRows, numberOfFrames);
	mFramesPerSecond = frameRate;
	mMilliSecondsBetweenFrames = 1000 / (double)mFramesPerSecond;
	mRemainingTimeBetweenFrames = mMilliSecondsBetweenFrames;
	mCurrentFrame = 0;
	mShouldLoop = shouldLoop;
}
Animation::~Animation()
{
	for (int i = 0; i < mSpriteFrames.size(); i++)
	{
		delete mSpriteFrames.at(i);
	}
	if (!mSpriteFrames.empty())
	{
		mSpriteFrames.clear();
	}
	mFramesPerSecond = 0;
	mMilliSecondsBetweenFrames = 0;
	mCurrentFrame = 0;
	mShouldLoop = false;
}
void Animation::addSprite(Sprite* newSprite) //pass in Sprite object and add it to the end of spriteFrames vector
{
	mSpriteFrames.push_back(newSprite);
}
void Animation::addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames) //pass in GraphicsBuffer object and the number of sprites on sheet (columns and rows)
{
	int framesProcessed = 0;
	//create sprites using nested for-loop that traverses the GraphicsBuffer bitmap (probably will call addSprite() to add in new Sprites to vector)
	for (int i = 0; i < columnsAndRows.getX(); i++)
	{
		for (int j = 0; j < columnsAndRows.getY(); j++)
		{
			Vector2D origin = Vector2D(0.0f, 0.0f);

			float spriteWidth = spriteSheet->getWidth() / columnsAndRows.getX();
			float spriteHeight = spriteSheet->getHeight() / columnsAndRows.getY();
			Vector2D spriteWidthAndHeight = Vector2D(spriteWidth, spriteHeight);

			Vector2D spriteOrigin = Vector2D((0.0f + spriteWidthAndHeight.getX()*j), (0.0f + spriteWidthAndHeight.getY() * i));

			mSpriteFrames.push_back(new Sprite(spriteSheet, spriteOrigin, columnsAndRows));
			framesProcessed += 1;
			if (framesProcessed == numberOfFrames)
			{
				break;
			}
		}
	}
}
void Animation::updateAnimation(double deltaTime) //move to next frame in animation
{
	mRemainingTimeBetweenFrames -= deltaTime;
	if (mRemainingTimeBetweenFrames <= 0.0f)
	{
		if (mCurrentFrame < mSpriteFrames.size()-1)
		{
			mCurrentFrame++;
			mRemainingTimeBetweenFrames = mMilliSecondsBetweenFrames;
		}
		else
		{
			if (mShouldLoop)
			{
				mCurrentFrame = 0;
			}
		}
	}
	//Just increment mCurrentFrame by 1.
}
Sprite* Animation::getCurrentSprite() //return current frame of animation
{
	return mSpriteFrames.at(mCurrentFrame);
}
void Animation::speedUpAnimation() //Increase framerate of animation by 1 FPS
{
	mFramesPerSecond += 1;
	mMilliSecondsBetweenFrames = 1 / (double)mFramesPerSecond;
}
void Animation::slowDownAnimation() //Decrease framerate of animation by 1 FPS
{
	mFramesPerSecond -= 1;
	if (mFramesPerSecond > 0)
	{
		mMilliSecondsBetweenFrames = 1000 / (double)mFramesPerSecond;
	}
	else
	{
		mFramesPerSecond = 0;
		mMilliSecondsBetweenFrames = -10;
	}
}
void Animation::speedUpAnimation(int frameRateIncrease)
{
	mFramesPerSecond += frameRateIncrease;
	mMilliSecondsBetweenFrames = 1000 / (double)mFramesPerSecond;
}
void Animation::slowDownAnimation(int frameRateDecrease)
{
	mFramesPerSecond -= frameRateDecrease;
	if (mFramesPerSecond > 0)
	{
		mMilliSecondsBetweenFrames = 1000 / (double)mFramesPerSecond;
	}
	else
	{
		mFramesPerSecond = 0;
		mMilliSecondsBetweenFrames = -10;
	}
}
int Animation::getFrameRate()
{
	return mFramesPerSecond;
}
double Animation::getMSBetweenFrames()
{
	return mMilliSecondsBetweenFrames;
}
void Animation::setMSBetweenFrames(int MilliSeconds)
{
	mMilliSecondsBetweenFrames = MilliSeconds;
}