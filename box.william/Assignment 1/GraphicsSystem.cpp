#include "GraphicsSystem.h"
GraphicsSystem::GraphicsSystem() 
{
	mGraphicsSystemDisplay = NULL;
	mGraphicsSystemBackBuffer = NULL;
}
GraphicsSystem::~GraphicsSystem() {
	graphicsSystemCleanUp();
}
void GraphicsSystem::graphicsSystemInit(int width, int height) 
{
	this->mWidth = width;
	this->mHeight = height;
	mGraphicsSystemDisplay = al_create_display(width,height);
	assert(mGraphicsSystemDisplay);
	mGraphicsSystemBackBuffer = al_get_backbuffer(mGraphicsSystemDisplay);
}
void GraphicsSystem::graphicsSystemCleanUp() 
{
	al_destroy_display(mGraphicsSystemDisplay);
	mGraphicsSystemDisplay = NULL;
}

int GraphicsSystem::getHeight() 
{
	return mHeight;
}

int GraphicsSystem::getWidth() 
{
	return mWidth;
}

ALLEGRO_BITMAP* GraphicsSystem::getBackBuffer() 
{
	return mGraphicsSystemBackBuffer;
}

void GraphicsSystem::flip() 
{
	al_flip_display();
}

void GraphicsSystem::draw(Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX, float spriteScaleY)
{
	al_set_target_bitmap(mGraphicsSystemBackBuffer);
	float scaledX = spriteToDraw->getSpriteWidth() * spriteScaleX;
	float scaledY = spriteToDraw->getSpriteHeight() * spriteScaleY;

	al_draw_scaled_bitmap(spriteToDraw->getSpriteGraphicsBuffer()->getGraphicsBufferBitMap(), 
		spriteToDraw->getSpriteSourceLocation().getX(), 
		spriteToDraw->getSpriteSourceLocation().getY(), 
		spriteToDraw->getSpriteWidth(), 
		spriteToDraw->getSpriteHeight(), 
		spritePosition.getX(), 
		spritePosition.getY(), 
		scaledX, 
		scaledY, 
		0);
}
void GraphicsSystem::draw(GraphicsBuffer* graphicsBufferToDraw,Vector2D graphicsBufferPosition, float spriteScaleX, float spriteScaleY)
{
	Vector2D origin = Vector2D(0, 0);
	float scaledX = graphicsBufferToDraw->getWidth() * spriteScaleX;
	float scaledY = graphicsBufferToDraw->getHeight() * spriteScaleY;
	al_draw_scaled_bitmap(graphicsBufferToDraw->getGraphicsBufferBitMap(), 
		origin.getX(), 
		origin.getY(), 
		graphicsBufferToDraw->getWidth(), 
		graphicsBufferToDraw->getHeight(), 
		graphicsBufferPosition.getX(), 
		graphicsBufferPosition.getY(), 
		scaledX, 
		scaledY, 
		0);
}
void GraphicsSystem::draw(GraphicsBuffer* graphicsBufferToDrawOn, Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX, float spriteScaleY)
{
	al_set_target_bitmap(graphicsBufferToDrawOn->getGraphicsBufferBitMap());
	float scaledX = spriteToDraw->getSpriteWidth() * spriteScaleX;
	float scaledY = spriteToDraw->getSpriteHeight() * spriteScaleY;
	al_draw_scaled_bitmap(spriteToDraw->getSpriteGraphicsBuffer()->getGraphicsBufferBitMap(), 
		spriteToDraw->getSpriteSourceLocation().getX(), 
		spriteToDraw->getSpriteSourceLocation().getY(), 
		spriteToDraw->getSpriteWidth(), 
		spriteToDraw->getSpriteHeight(), 
		spritePosition.getX(), 
		spritePosition.getY(), 
		scaledX, 
		scaledY, 
		0);
}
void GraphicsSystem::writeText(Font* fontToWriteWith, Vector2D fontPosition, Color fontColor, std::string stringToDraw)
{
	al_draw_text(fontToWriteWith->getFont(), 
		fontColor.getColor(), 
		fontPosition.getX(), 
		fontPosition.getY(), 
		0, 
		stringToDraw.c_str());
}
void GraphicsSystem::saveBuffer(){}