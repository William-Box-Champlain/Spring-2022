#include "Sprite.h"
Sprite::Sprite(GraphicsBuffer* spriteGraphicsBuffer, Vector2D spriteSourceLocation = Vector2D(0.0f , 0.0f), Vector2D sourceColumnsAndRows = Vector2D(1.0f , 1.0f)) //sourceColumnsAndRows is the number of sprite tiles in the source file
{
	this->mSpriteGraphicsBuffer = spriteGraphicsBuffer;
	this->mSpriteSourceLocation = spriteSourceLocation;
	int sourceWidth = spriteGraphicsBuffer->getWidth();
	int spriteWidth = sourceWidth / sourceColumnsAndRows.getX();
	int sourceHeight = spriteGraphicsBuffer->getHeight();
	int spriteHeight = sourceHeight / sourceColumnsAndRows.getY();
	Vector2D spriteDimensions = Vector2D(spriteWidth, spriteHeight);
	this->mSpriteWidthAndHeight = spriteDimensions;
}
Sprite::~Sprite() 
{
	//delete mSpriteGraphicsBuffer;
	mSpriteGraphicsBuffer = nullptr;
}
Vector2D Sprite::getSpriteSourceLocation() 
{
	return mSpriteSourceLocation;
}
int Sprite::getSpriteWidth() {return mSpriteWidthAndHeight.getX();}

int Sprite::getSpriteHeight() {return mSpriteWidthAndHeight.getY();}

Vector2D Sprite::getSpriteDimensions()
{
	return mSpriteWidthAndHeight;
}

GraphicsBuffer* Sprite::getSpriteGraphicsBuffer() {return mSpriteGraphicsBuffer;}