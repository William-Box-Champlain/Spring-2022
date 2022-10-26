#include "ClickableButton.h"

ClickableButton::ClickableButton(Animation* unitAnimation, Vector2D startingPosition, Clickables type):Unit(unitAnimation, startingPosition)
{
	mType = type;
}

void ClickableButton::clickButton()
{
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(ClickableEvent(mType));
}

Clickables ClickableButton::getButtonType()
{
	return mType;
}
