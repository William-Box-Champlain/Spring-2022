#pragma once
#include "Unit.h"
#include "ClickableEvent.h"
class ClickableButton:public Unit
{
public:
	ClickableButton(Animation* unitAnimation, Vector2D startingPosition, Clickables type);
	~ClickableButton();
	void clickButton();
	Clickables getButtonType();
private:
	Clickables mType;
};