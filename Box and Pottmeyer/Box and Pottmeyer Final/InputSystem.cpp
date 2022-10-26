#include "InputSystem.h"
#include "MouseInputEvent.h"
#include "KeyboardInputEvent.h"
InputSystem::InputSystem()
{

}
InputSystem::~InputSystem()
{
	
}
void InputSystem::inputSystemInitializer()
{
	/*al_install_keyboard();
	al_install_mouse();
	mpQueue = al_create_event_queue();
	al_register_event_source(mpQueue, al_get_keyboard_event_source());
	al_register_event_source(mpQueue, al_get_mouse_event_source());*/
	mpEventSystem = EventSystem::getInstance();
}
void InputSystem::inputSystemCleanUp()
{

}
void InputSystem::initialize()
{
}
void InputSystem::update()
{
	
	/*while (!al_is_event_queue_empty(mpQueue))
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
	}*/
	SDL_Event event;
	Vector2D direction;
	EventSystem* tempEventSystem = EventSystem::getInstance();
	while (SDL_PollEvent(&event))
	{
		/*if (event.type == SDL_MOUSEMOTION)
		{
			std::cout << "x: " << event.motion.x << " y:" << event.motion.y << std::endl;
		}*/
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				tempEventSystem->fireEvent(LevelEvents(LevelEventType::PAUSE_GAME));
				break;
			case SDLK_SPACE:
				tempEventSystem->fireEvent(LevelEvents(LevelEventType::START_GAME));
				break;
			case SDLK_UP:
			case SDLK_w:
				direction = Vector2D(0, -1);
				tempEventSystem->fireEvent(MoveEvent(direction));
				break;
			case SDLK_DOWN:
			case SDLK_s:
				direction = Vector2D(0, 1);
				tempEventSystem->fireEvent(MoveEvent(direction));
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				direction = Vector2D(1, 0);
				tempEventSystem->fireEvent(MoveEvent(direction));
				break;
			case SDLK_LEFT:
			case SDLK_a:
				direction = Vector2D(-1, 0);
				tempEventSystem->fireEvent(MoveEvent(direction));
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				Vector2D temp = Vector2D((int)event.motion.x, (int)event.motion.y);
				tempEventSystem->fireEvent(MouseInputEvent(temp, (MouseOutputs)event.button.button));
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			
		}
	}
}
//bool InputSystem::isKeyDown(int keyBoardNum)
//{
//	al_get_keyboard_state(&mKeyboardState);
//	return al_key_down(&mKeyboardState, keyBoardNum);
//}
//bool InputSystem::isMouseDown(int mouseInput)
//{
//	al_get_mouse_state(&mMouseState);
//	return al_mouse_button_down(&mMouseState, mouseInput);
//}
//void InputSystem::updateKeyboardAndMouseState()
//{
//	al_get_keyboard_state(&mKeyboardState);
//	al_get_mouse_state(&mMouseState);
//}
//ALLEGRO_KEYBOARD_STATE* InputSystem::getKeyboardState()
//{
//	return &mKeyboardState;
//}
//ALLEGRO_MOUSE_STATE* InputSystem::getMouseState()
//{
//	return &mMouseState;
//}
//Vector2D InputSystem::getMousePosition()
//{
//	return Vector2D((al_get_mouse_state_axis(&mMouseState, 0)), (al_get_mouse_state_axis(&mMouseState, 1)));
//}