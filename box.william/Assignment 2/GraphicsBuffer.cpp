#include "GraphicsBuffer.h"
GraphicsBuffer::GraphicsBuffer(std::string filePath, std::string fileName)
{
	mGraphicsBufferBitMap = al_load_bitmap((filePath + fileName).c_str());
}
GraphicsBuffer::GraphicsBuffer(int width, int height) 
{
	mGraphicsBufferBitMap = al_create_bitmap(400, 300);
}
GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap(mGraphicsBufferBitMap);
}
int GraphicsBuffer::getHeight() 
{
	return al_get_bitmap_height(mGraphicsBufferBitMap);
}

int GraphicsBuffer::getWidth() 
{
	return al_get_bitmap_width(mGraphicsBufferBitMap);
}

ALLEGRO_BITMAP* GraphicsBuffer::getGraphicsBufferBitMap() 
{
	return mGraphicsBufferBitMap;
}
void GraphicsBuffer::setGraphicsBufferToColor(Color newColor) 
{
	ALLEGRO_BITMAP* originalBitmap = al_get_target_bitmap();
	al_set_target_bitmap(mGraphicsBufferBitMap);
	al_clear_to_color(newColor.getColor());
	al_set_target_bitmap(originalBitmap);
}