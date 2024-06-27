#include "SDLGraphicsProgram.hpp"
#include <sstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h, std::string title) : screenWidth(w), screenHeight(h)
{
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow(title.c_str(), screenWidth, screenHeight, SDL_WINDOW_OPENGL);

        // Check if Window did not create.
        if (gWindow == NULL)
        {
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, NULL, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if (gRenderer == NULL)
        {
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if (!success)
    {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    }
    else
    {
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }
}

// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram()
{
    // Destroy window
    SDL_DestroyWindow(gWindow);
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    // Quit SDL subsystems
    SDL_Quit();
}

// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL()
{
    // Success flag
    bool success = true;

    return success;
}

// clear
// Clears the screen
void SDLGraphicsProgram::clear(int r, int g, int b, int a)
{
    // Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
    SDL_RenderClear(gRenderer);
}
// Flip
// The flip function gets called once per loop
// It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip()
{
    // Nothing yet!
    SDL_RenderPresent(gRenderer);
}

float SDLGraphicsProgram::getDeltaTime()
{
    if (frameStartTime != 0.0f)
    {
        deltaTime = (SDL_GetTicks() - frameStartTime) / 1000.0f;
    }
    frameStartTime = SDL_GetTicks();
    return deltaTime;
}

void SDLGraphicsProgram::delay(int milliseconds)
{
    SDL_Delay(milliseconds);
}

// Loops forever!
void SDLGraphicsProgram::loop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        } // End SDL_PollEvent loop.

        // Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
    }

    // Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::getSDLWindow()
{
    return gWindow;
}

SDL_Renderer *SDLGraphicsProgram::getSDLRenderer()
{
    return gRenderer;
}

// Okay, render our rectangles!
void SDLGraphicsProgram::drawRectangle(bool fill, float x, float y, float w, float h, int r, int g, int b)
{
    SDL_FRect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0);
    if (fill)
        SDL_RenderFillRect(gRenderer, &fillRect);
    else
        SDL_RenderRect(gRenderer, &fillRect);
}

int SDLGraphicsProgram::getScreenWidth()
{
    return screenWidth;
}

int SDLGraphicsProgram::getScreenHeight()
{
    return screenHeight;
}
