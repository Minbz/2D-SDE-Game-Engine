#include "Input.hpp"
#include <cstdint>

Input::Input()
{
}

Input::~Input()
{
}

bool Input::isUpKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP];
}

bool Input::isDownKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN];
}

bool Input::isLeftKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT];
}

bool Input::isRightKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT];
}

bool Input::isESCKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE];
}

bool Input::isXKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_X];
}

bool Input::isEKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_E];
}

bool Input::isSKeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S];
}

bool Input::is1KeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_1];
}

bool Input::is2KeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_2];
}

bool Input::is3KeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_3];
}

bool Input::is4KeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_4];
}

bool Input::is5KeyDown()
{
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_5];
}

std::vector<float> Input::GetMouseClickPosition()
{
    float x = 0;
    float y = 0;
    std::vector<float> mouseState;

    uint32_t result = SDL_GetMouseState(&x, &y);
    if (result & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        mouseState.push_back(x);
        mouseState.push_back(y);
    }

    return mouseState;
}

std::vector<float> Input::GetMousePosition()
{
    float x = 0;
    float y = 0;
    std::vector<float> mouseState;

    SDL_GetMouseState(&x, &y);
    mouseState.push_back(x);
    mouseState.push_back(y);

    return mouseState;
}

bool Input::isQuitClicked()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return true;
        }
    }
    return false;
}