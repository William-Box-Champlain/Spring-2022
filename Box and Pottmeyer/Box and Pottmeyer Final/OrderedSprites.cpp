#include "OrderedSprites.h"
OrderedSprites::OrderedSprites()
{

}
OrderedSprites::OrderedSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames)
{
	addMultipleSprites(spriteSheet, columnsAndRows, numberOfFrames);
}
OrderedSprites::~OrderedSprites()
{
	for (auto p : mSpriteFrames)
	{
		delete p;
	}
	mSpriteFrames.clear();
}
void OrderedSprites::addSprite(Sprite* newSprite)
{
	mSpriteFrames.push_back(newSprite);
}
Sprite* OrderedSprites::getSprite(int i)
{
	return mSpriteFrames.at(i);
}
int OrderedSprites::size()
{
	return mSpriteFrames.size();
}
std::vector<Sprite*> OrderedSprites::getVector()
{
	return mSpriteFrames;
}