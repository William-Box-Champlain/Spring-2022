#include "Animation.h"
Animation::Animation()
{
	mFramesPerSecond = 0;
	mMilliSecondsBetweenFrames = 0;
	mRemainingTimeBetweenFrames = 0;
	mCurrentFrame = 0;
	mpOrderedSprites = NULL;
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
Animation::Animation(OrderedSprites* sprites, int frameRate, bool shouldLoop)
{
	mpOrderedSprites = sprites;
	mFramesPerSecond = frameRate;
	mMilliSecondsBetweenFrames = 1000 / (double)mFramesPerSecond;
	mRemainingTimeBetweenFrames = mMilliSecondsBetweenFrames;
	mCurrentFrame = 0;
	mShouldLoop = shouldLoop;
}
Animation::~Animation()
{
	mpOrderedSprites = nullptr;
	mFramesPerSecond = 0;
	mMilliSecondsBetweenFrames = 0;
	mCurrentFrame = 0;
	mShouldLoop = false;
}
void Animation::addSprite(Sprite* newSprite) //pass in Sprite object and add it to the end of spriteFrames vector
{
	mpOrderedSprites->addSprite(newSprite);
}
void Animation::addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames) //pass in GraphicsBuffer object and the number of sprites on sheet (columns and rows)
{
	mpOrderedSprites = new OrderedSprites(spriteSheet, columnsAndRows, numberOfFrames);
}
void Animation::updateAnimation(double deltaTime) //move to next frame in animation
{
	mRemainingTimeBetweenFrames -= deltaTime;
	if (mRemainingTimeBetweenFrames <= 0.0f)
	{
		if ((unsigned int)mCurrentFrame < (unsigned int)mpOrderedSprites->getVector().size()-1)
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
	return mpOrderedSprites->getSprite(mCurrentFrame);
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