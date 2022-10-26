#include <allegro5/allegro5.h>
#include <Trackable.h>
#include <Vector2D.h>
#pragma once
class InputSystem :public Trackable
{
    enum KeyCodes
    {
        F_Key = ALLEGRO_KEY_F,
        S_Key = ALLEGRO_KEY_S,
        Enter_Key = ALLEGRO_KEY_ENTER,
        Escape_Key = ALLEGRO_KEY_ESCAPE
    };
    enum MouseOutputs
    {
        Left_Mouse,
        Right_Mouse,
        Middle_Mouse
    };
public:
    InputSystem();
    ~InputSystem();
    void inputSystemInitializer();
    void inputSystemCleanUp();

    bool isKeyDown(int keyBoardNum);

    bool isMouseDown(int mouseInput); // 1 for left mouse, 2 for right mouse, 

private:
    Vector2D getMousePosition();

    void updateKeyboardAndMouseState();


    ALLEGRO_KEYBOARD_STATE* getKeyboardState();
    ALLEGRO_MOUSE_STATE* getMouseState();

    ALLEGRO_KEYBOARD_STATE mKeyboardState;
    ALLEGRO_MOUSE_STATE mMouseState;

    friend class Game;
};