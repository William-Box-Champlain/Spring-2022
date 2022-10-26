#include <Trackable.h>
#include "Sprite.h"
#include <vector>
#pragma once

class OrderedSprites:public Trackable
{
public:
	OrderedSprites();
	OrderedSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames);
	~OrderedSprites();
	void addSprite(Sprite* newSprite);
	void addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D columnsAndRows, int numberOfFrames)
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

				Vector2D spriteOrigin = Vector2D((0.0f + spriteWidthAndHeight.getX() * j), (0.0f + spriteWidthAndHeight.getY() * i));

				mSpriteFrames.push_back(new Sprite(spriteSheet, spriteOrigin, columnsAndRows));
				framesProcessed += 1;
				if (framesProcessed == numberOfFrames)
				{
					break;
				}
			}
		}
	}
	Sprite* getSprite(int i);
	int size();
	std::vector<Sprite*> getVector();
private:
	std::vector<Sprite*> mSpriteFrames;
};