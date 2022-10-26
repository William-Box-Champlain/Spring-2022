#include "GraphicsBuffer.h"
GraphicsBuffer::GraphicsBuffer(std::string filePath, std::string fileName)
{
	mGraphicsBufferBitMap = SDL_LoadBMP((filePath + fileName).c_str());
	mOwnsGraphicsBuffer = false;
}
GraphicsBuffer::GraphicsBuffer(std::string completeFilePath)
{
	mGraphicsBufferBitMap = SDL_LoadBMP(completeFilePath.c_str());
	mOwnsGraphicsBuffer = false;
}
GraphicsBuffer::GraphicsBuffer(int width, int height) 
{
	mGraphicsBufferBitMap = SDL_CreateRGBSurface(0, 400, 300, 1, 0, 0, 0, 255);
	mOwnsGraphicsBuffer = false;
}
GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsGraphicsBuffer)
	{
		//al_destroy_bitmap(mGraphicsBufferBitMap);
		//see folowing link for details: https://thenumbat.github.io/cpp-course/sdl2/01/01.html#:~:text=As%20you%20might%20expect%2C%20SDL_DestroyWindow%20%28%29%20does%20just,surface%29.%20SDL_DestroyWindow%28win%29%3B%20win%20%3D%20NULL%3B%20winSurface%20%3D%20NULL%3B
		SDL_FreeSurface(mGraphicsBufferBitMap);
	}
}
int GraphicsBuffer::getHeight() 
{
	return mGraphicsBufferBitMap->h;
}

int GraphicsBuffer::getWidth() 
{
	return mGraphicsBufferBitMap->w;
}

SDL_Surface* GraphicsBuffer::getGraphicsBufferBitMap() 
{
	return mGraphicsBufferBitMap;
}
void GraphicsBuffer::setGraphicsBufferToColor(Color newColor) 
{
	/*
	SDL_Surface* originalBitmap = al_get_target_bitmap();
	al_set_target_bitmap(mGraphicsBufferBitMap);
	al_clear_to_color(newColor.getColor());
	al_set_target_bitmap(originalBitmap);
	*/

	SDL_SetSurfaceColorMod(mGraphicsBufferBitMap, newColor.getColor().r, newColor.getColor().g, newColor.getColor().b);
}