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
	mpQueue = al_create_event_queue();
	al_register_event_source(mpQueue, al_get_keyboard_event_source());
	al_register_event_source(mpQueue, al_get_mouse_event_source());

}
void InputSystem::inputSystemCleanUp()
{

}
void InputSystem::initialize()
{
}
void InputSystem::update()
{
	EventSystem* eventSystem = EventSystem::getInstance();	

	while (!al_is_event_queue_empty(mpQueue))
	{
		ALLEGRO_EVENT event;
		al_get_next_event(mpQueue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			Vector2D direction;
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				direction = Vector2D(0, -1);
				eventSystem->fireEvent(MoveEvent(direction));
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				direction = Vector2D(0, 1);
				eventSystem->fireEvent(MoveEvent(direction));
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				direction = Vector2D(-1, 0);
				eventSystem->fireEvent(MoveEvent(direction));
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				direction = Vector2D(1, 0);
				eventSystem->fireEvent(MoveEvent(direction));
				break;
			case ALLEGRO_KEY_SPACE:
				eventSystem->fireEvent(LevelEvents(LevelEventType::START_GAME));
				break;
			case ALLEGRO_KEY_BACKSPACE:
				eventSystem->fireEvent(SnakeEvent(SnakeEventType::SHRINK));
				break;
			case ALLEGRO_KEY_ESCAPE:
				eventSystem->fireEvent(LevelEvents(LevelEventType::CLOSE_GAME));
				break;
			case ALLEGRO_KEY_ENTER:
				eventSystem->fireEvent(LevelEvents(LevelEventType::RESTART_GAME));
				break;
			default:
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			Vector2D position = getMousePosition();
		}
	}
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