#include <EventSystem.h>
//#include <allegro5/allegro.h>
#include <SDL.h>
#include "MoveEvent.h"
#include "LevelEvents.h"
#include "SnakeEvent.h"
#pragma once

enum class KeyCodes
{
    A = SDLK_a, B = SDLK_b, C = SDLK_c, D = SDLK_d, E = SDLK_e,
    F = SDLK_f, G = SDLK_g, H = SDLK_h, I = SDLK_i, J = SDLK_j,
    K = SDLK_k, L = SDLK_l, M = SDLK_m, N = SDLK_n, O = SDLK_o,
    P = SDLK_p, Q = SDLK_q, R = SDLK_r, S = SDLK_s, T = SDLK_t,
    U = SDLK_u, V = SDLK_v, W = SDLK_w, X = SDLK_x, Y = SDLK_y,
    Z = SDLK_z,

    ONE = SDLK_1, TWO = SDLK_2, THREE = SDLK_3,
    FOUR = SDLK_4, FIVE = SDLK_5, SIX = SDLK_6,
    SEVEN = SDLK_7, EIGHT = SDLK_8, NINE = SDLK_9,
    ZERO = SDLK_0,

    ESCAPE = SDLK_ESCAPE,
    SPACE = SDLK_SPACE,

    RIGHT_ARROW = SDLK_RIGHT,
    LEFT_ARROW = SDLK_LEFT,
    UP_ARROW = SDLK_UP,
    DOWN_ARROW = SDLK_DOWN
};

enum class MouseOutputs
{
    LEFT_MOUSE = SDL_BUTTON_LEFT,
    Right_Mouse = SDL_BUTTON_RIGHT,
    Middle_Mouse = SDL_BUTTON_MIDDLE
};

class InputSystem :public Trackable
{
public:
    InputSystem();
    ~InputSystem();
    void inputSystemInitializer();

    void update();

    //bool isKeyDown(int keyBoardNum);

    //bool isMouseDown(int mouseInput); // 1 for left mouse, 2 for right mouse, 

private:
    EventSystem* mpEventSystem;
    //ALLEGRO_EVENT_QUEUE* mpQueue = nullptr;
    SDL_Event mpSDLQueue;

    Vector2D getMousePosition();

    void updateKeyboardAndMouseState();


    /*ALLEGRO_KEYBOARD_STATE* getKeyboardState();
    ALLEGRO_MOUSE_STATE* getMouseState();

    ALLEGRO_KEYBOARD_STATE mKeyboardState;
    ALLEGRO_MOUSE_STATE mMouseState;*/

    void initialize();
    void inputSystemCleanUp();

    friend class Game;
};