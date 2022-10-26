#pragma once
#include "GameEvents.h"

enum Clickables 
{
    START,
    DIFFICULTY,
    LOAD,
    SAVE,
    RESTART,
    QUIT,
    LANGUAGE
};

class ClickableEvent:public GameEvents
{
public:
    ClickableEvent(Clickables type);
    ~ClickableEvent();
    Clickables getType();
private:
    Clickables mClickableType;
};