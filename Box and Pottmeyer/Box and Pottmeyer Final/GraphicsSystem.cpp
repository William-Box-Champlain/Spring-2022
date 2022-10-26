#include "GraphicsSystem.h"
GraphicsSystem::GraphicsSystem() 
{
	/*mGraphicsSystemDisplay = NULL;
	mGraphicsSystemBackBuffer = NULL;*/
}
GraphicsSystem::~GraphicsSystem() {
	//graphicsSystemCleanUp();
	SDLCleanUp();
}
void GraphicsSystem::graphicsSystemInit(int width, int height) 
{
	/*this->mWidth = width;
	this->mHeight = height;
	this->mGraphicsSystemDisplay = al_create_display(mWidth,mHeight);
	assert(mGraphicsSystemDisplay);
	mGraphicsSystemBackBuffer = al_get_backbuffer(mGraphicsSystemDisplay);*/
	SDLInit(width, height);

}
//void GraphicsSystem::graphicsSystemCleanUp() 
//{
//	//al_destroy_bitmap(mGraphicsSystemBackBuffer);
//	al_destroy_display(mGraphicsSystemDisplay);
//	mGraphicsSystemDisplay = nullptr;
//	mGraphicsSystemBackBuffer = nullptr;
//}

int GraphicsSystem::getHeight() 
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(mpGraphicsSystemDisplay, &width, &height);
	return height;
}

int GraphicsSystem::getWidth() 
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(mpGraphicsSystemDisplay, &width, &height);
	return width;
}

//ALLEGRO_BITMAP* GraphicsSystem::getBackBuffer() 
//{
//	return mGraphicsSystemBackBuffer;
//}

void GraphicsSystem::flip() 
{
	//al_flip_display();
	SDL_RenderPresent(mpGraphicsSystemRenderer);
}

//void GraphicsSystem::draw(Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX, float spriteScaleY)
//{
//	al_set_target_bitmap(mGraphicsSystemBackBuffer);
//	float scaledX = spriteToDraw->getSpriteWidth() * spriteScaleX;
//	float scaledY = spriteToDraw->getSpriteHeight() * spriteScaleY;
//
//	al_draw_scaled_bitmap(spriteToDraw->getSpriteGraphicsBuffer()->getGraphicsBufferBitMap(), 
//		spriteToDraw->getSpriteSourceLocation().getX(), 
//		spriteToDraw->getSpriteSourceLocation().getY(), 
//		spriteToDraw->getSpriteWidth(), 
//		spriteToDraw->getSpriteHeight(), 
//		spritePosition.getX(), 
//		spritePosition.getY(), 
//		scaledX, 
//		scaledY, 
//		0);
//}
void GraphicsSystem::draw(GraphicsBuffer* graphicsBufferToDraw)
{
	SDL_Texture* tempTexture =	SDL_CreateTextureFromSurface(mpGraphicsSystemRenderer, graphicsBufferToDraw->getGraphicsBufferBitMap());
	SDL_Rect spriteRectangle;

	spriteRectangle.x = graphicsBufferToDraw->getWidth();
	spriteRectangle.y = graphicsBufferToDraw->getHeight();
	spriteRectangle.w = graphicsBufferToDraw->getWidth();
	spriteRectangle.h = graphicsBufferToDraw->getHeight();

	SDL_RenderCopy(mpGraphicsSystemRenderer, tempTexture, &spriteRectangle, &spriteRectangle);
	SDL_DestroyTexture(tempTexture);
}
void GraphicsSystem::draw(Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX, float spriteScaleY)
{
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(mpGraphicsSystemRenderer, spriteToDraw->getSpriteGraphicsBuffer()->getGraphicsBufferBitMap());
	SDL_Rect spriteRectangle;
	SDL_Rect locationRectangle;

	spriteRectangle.x = spriteToDraw->getSpriteSourceLocation().getX();;
	spriteRectangle.y = spriteToDraw->getSpriteSourceLocation().getY();;
	spriteRectangle.w = (spriteToDraw->getSpriteWidth() * 1);
	spriteRectangle.h = (spriteToDraw->getSpriteHeight() * 1);

	locationRectangle.x = spritePosition.getX();
	locationRectangle.y = spritePosition.getY();
	//std::cout << spriteToDraw->getSpriteHeight();
	locationRectangle.w = (spriteToDraw->getSpriteWidth() * spriteScaleX);
	locationRectangle.h = (spriteToDraw->getSpriteHeight() * spriteScaleY);

	SDL_RenderCopy(mpGraphicsSystemRenderer, tempTexture, &spriteRectangle, &locationRectangle);
	SDL_DestroyTexture(tempTexture);
}
void GraphicsSystem::clearFrame()
{
	SDL_RenderClear(mpGraphicsSystemRenderer);
}
//void GraphicsSystem::draw(GraphicsBuffer* graphicsBufferToDraw,Vector2D graphicsBufferPosition, float spriteScaleX, float spriteScaleY)
//{
//	Vector2D origin = Vector2D(0, 0);
//	float scaledX = graphicsBufferToDraw->getWidth() * spriteScaleX;
//	float scaledY = graphicsBufferToDraw->getHeight() * spriteScaleY;
//	al_draw_scaled_bitmap(graphicsBufferToDraw->getGraphicsBufferBitMap(), 
//		origin.getX(), 
//		origin.getY(), 
//		graphicsBufferToDraw->getWidth(), 
//		graphicsBufferToDraw->getHeight(), 
//		graphicsBufferPosition.getX(), 
//		graphicsBufferPosition.getY(), 
//		scaledX, 
//		scaledY, 
//		0);
//}
//void GraphicsSystem::draw(GraphicsBuffer* graphicsBufferToDrawOn, Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX, float spriteScaleY)
//{
//	ALLEGRO_BITMAP* originalBitMap = al_get_target_bitmap();
//	al_set_target_bitmap(graphicsBufferToDrawOn->getGraphicsBufferBitMap());
//	float scaledX = spriteToDraw->getSpriteWidth() * spriteScaleX;
//	float scaledY = spriteToDraw->getSpriteHeight() * spriteScaleY;
//	al_draw_scaled_bitmap(spriteToDraw->getSpriteGraphicsBuffer()->getGraphicsBufferBitMap(), 
//		spriteToDraw->getSpriteSourceLocation().getX(), 
//		spriteToDraw->getSpriteSourceLocation().getY(), 
//		spriteToDraw->getSpriteWidth(), 
//		spriteToDraw->getSpriteHeight(), 
//		spritePosition.getX(), 
//		spritePosition.getY(), 
//		scaledX, 
//		scaledY, 
//		0);
//	al_set_target_bitmap(originalBitMap);
//}
void GraphicsSystem::writeText(Font* fontToWriteWith, Vector2D fontPosition, Color fontColor, std::string stringToDraw)
{
	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(fontToWriteWith->getFont(), stringToDraw.c_str(), fontColor.getColor());

	if (!textSurface)
	{
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
		return;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mpGraphicsSystemRenderer, textSurface);
	SDL_Rect rectangle;
	rectangle.x = (int)fontPosition.getX() - (textSurface->w / 2);
	rectangle.y = (int)fontPosition.getY() - (textSurface->h / 2);
	rectangle.w = textSurface->w;
	rectangle.h = textSurface->h;
	SDL_RenderCopy(mpGraphicsSystemRenderer, textTexture, NULL, &rectangle);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
//void GraphicsSystem::saveBuffer(GraphicsBuffer* graphicsBufferToSave, std::string fileName)
//{
//	if (al_save_bitmap(fileName.c_str(), graphicsBufferToSave->getGraphicsBufferBitMap()))
//	{
//		std::cout << "Bitmap Saved";
//	}
//	else
//	{
//		std::cout << "Bitmap Failed to Save";
//	}
//}
void GraphicsSystem::SDLInit(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Init Error" << std::endl;
		system("pause");
		return;
	}

	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	mpGraphicsSystemDisplay = SDL_CreateWindow("gameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	SDL_SetWindowBordered(mpGraphicsSystemDisplay, SDL_TRUE);

	mpGraphicsSystemRenderer = SDL_CreateRenderer(mpGraphicsSystemDisplay, -1, 0);

	if (!mpGraphicsSystemRenderer)
	{
		std::cout << "Error initializing renderer" << std::endl;
		return;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init:" << TTF_GetError() << std::endl;
		return;
	}

	SDL_RenderClear(mpGraphicsSystemRenderer);
}
void GraphicsSystem::SDLCleanUp()
{
	if (mpGraphicsSystemDisplay)
	{
		SDL_DestroyWindow(mpGraphicsSystemDisplay);
		SDL_DestroyRenderer(mpGraphicsSystemRenderer);
		mpGraphicsSystemDisplay = nullptr;
		mpGraphicsSystemRenderer = nullptr;
	}
}