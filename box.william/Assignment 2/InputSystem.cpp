#include "InputSystem.h"
enum MouseOutputs
{
	Left_Mouse = 1,
	Right_Mouse = 2,
	Middle_Mouse = 3
};
InputSystem::InputSystem()
{

}
InputSystem::~InputSystem()
{
	
}
void InputSystem::inputSystemInitializer()
{
	al_install_keyboard();
	al_install_mouse();
}
void InputSystem::inputSystemCleanUp()
{

}
bool InputSystem::isKeyDown(int keyBoardNum)
{
	al_get_keyboard_state(&mKeyboardState);
	return al_key_down(&mKeyboardState, keyBoardNum);
}
bool InputSystem::isMouseDown(int mouseInput)
{
	al_get_mouse_state(&mMouseState);
	return al_mouse_button_down(&mMouseState, mouseInput);
}
void InputSystem::updateKeyboardAndMouseState()
{
	al_get_keyboard_state(&mKeyboardState);
	al_get_mouse_state(&mMouseState);
}
ALLEGRO_KEYBOARD_STATE* InputSystem::getKeyboardState()
{
	return &mKeyboardState;
}
ALLEGRO_MOUSE_STATE* InputSystem::getMouseState()
{
	return &mMouseState;
}
Vector2D InputSystem::getMousePosition()
{
	return Vector2D((al_get_mouse_state_axis(&mMouseState, 0)), (al_get_mouse_state_axis(&mMouseState, 1)));
}