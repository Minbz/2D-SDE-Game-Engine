#pragma once

#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
#include <SDL3/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include <string>

/**
 * A class that represents an SDLGraphicsProgram.
 * This class sets up a full graphics program using SDL.
 */
class SDLGraphicsProgram
{
public:
    /**
     * Constructor for SDLGraphicsProgram.
     * Creates a window and renderer for the program.
     * @param w The width of the window.
     * @param h The height of the window.
     * @param title The title of the window.
     * @see SDL_Window
     * @see SDL_Renderer
     */
    SDLGraphicsProgram(int w, int h, std::string title);

    /**
     * Destructor for SDLGraphicsProgram.
     * Kill the window.
     */
    ~SDLGraphicsProgram();

    /**
     * Set up the success flag.
     * @return True.
     */
    bool initGL();

    /**
     * Clear the screen to a specified color.
     * @param r The red value of the color.
     * @param g The green value of the color.
     * @param b The blue value of the color.
     * @param a The alpha value of the color.
     * @see SDL_SetRenderDrawColor
     */
    void clear(int r, int g, int b, int a);

    /**
     * Render the screen.
     * It gets called once per loop.
     */
    void flip();

    /**
     * Get the time since the last frame.
     * @return The time since the last frame.
     */
    float getDeltaTime();

    /**
     * Delay the program for a specified number of milliseconds.
     */
    void delay(int milliseconds);

    /**
     * Set up a main loop.
     * This loop will keep the program running until the user exits.
     * @see SDL_PollEvent
     */
    void loop();

    /**
     * Get Pointer to Window
     * @return The SDL_Window pointer.
     */
    SDL_Window *getSDLWindow();

    /**
     * Get Pointer to Renderer
     * @return The SDL_Renderer pointer.
     */
    SDL_Renderer *getSDLRenderer();

    /**
     * Draw a rectangle on the screen.
     * If fill is true, the rectangle will be filled.
     * @param fill Whether the rectangle should be filled or not.
     * @param x The x position of the rectangle.
     * @param y The y position of the rectangle.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @param r The red value of the color.
     * @param g The green value of the color.
     * @param b The blue value of the color.
     * @see SDL_RenderRect
     * @see SDL_RenderFillRect
     */
    void drawRectangle(bool fill, float x, float y, float w, float h, int r, int g, int b);

    /**
     * Get the width of the screen.
     * @return The width of the screen.
     */
    int getScreenWidth();

    /**
     * Get the height of the screen.
     * @return The height of the screen.
     */
    int getScreenHeight();

private:
    /**
     * The width of the screen.
     */
    int screenHeight;

    /**
     * The height of the screen.
     */
    int screenWidth;

    /**
     * The window we'll be rendering to.
     */
    SDL_Window *gWindow;

    /**
     * The window renderer.
     */
    SDL_Renderer *gRenderer;

    /**
     * The time since the last frame.
     * Initialized to 60fps.
     */
    float deltaTime{1.0f / 60.0f};

    /**
     * The start time of the frame.
     * Initialized to 0 if the frame has not started.
     */
    float frameStartTime{0.0f};
};

#endif