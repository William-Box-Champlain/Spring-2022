#include <Trackable.h>
#include "Sprite.h"
#include <vector>

#pragma once
class Animation:public Trackable
{
public:
    Animation();
    Animation(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop);
    ~Animation();
    void addSprite(Sprite* newSprite); //Add single sprite to spriteFrames vector
    void addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames); //Add multiple sprites to spriteFrames using a GraphicsBuffer object
    void updateAnimation(double deltaTime);
    Sprite* getCurrentSprite();
    void speedUpAnimation();
    void slowDownAnimation();
    void speedUpAnimation(int frameRateIncrease);
    void slowDownAnimation(int frameRateDecrease);
    int getFrameRate();
    double getMSBetweenFrames();
    void setMSBetweenFrames(int MilliSeconds);
private:
    
    std::vector<Sprite*> mSpriteFrames;
    int mFramesPerSecond;
    double mMilliSecondsBetweenFrames;
    int mCurrentFrame; //Current frame the sprite animation is on.
    bool mShouldLoop;

    
};