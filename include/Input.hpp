#pragma once

#include <SDL3/SDL.h>
#include <vector>

/**
 * A struct that represents the input of the game.
 * Used to get the input from the user.
 * Note that it's not a component.
 * This is a static class, not meant to be instantiated.
 * It serves as a utility class to get input from the user.
 */
struct Input
{
    /**
     * Constructor for Input.
     * Do not use this constructor.
     * All functions in this class are static.
     */
    Input();

    /**
     * Destructor for Input.
     */
    ~Input();

    /**
     * Check if the up key is pressed.
     * @return True if the up key is pressed, false otherwise.
     */
    static bool isUpKeyDown();

    /**
     * Check if the down key is pressed.
     * @return True if the down key is pressed, false otherwise.
     */
    static bool isDownKeyDown();

    /**
     * Check if the left key is pressed.
     * @return True if the left key is pressed, false otherwise.
     */
    static bool isLeftKeyDown();

    /**
     * Check if the right key is pressed.
     * @return True if the right key is pressed, false otherwise.
     */
    static bool isRightKeyDown();

    /**
     * Check if the ESC key is pressed.
     * @return True if the ESC key is pressed, false otherwise.
     */
    static bool isESCKeyDown();

    /**
     * Check if the x key is pressed.
     * @return True if the x key is pressed, false otherwise.
     */
    static bool isXKeyDown();

    /**
     * Check if the e key is pressed.
     * @return True if the e key is pressed, false otherwise.
     */
    static bool isEKeyDown();

    /**
     * Check if the s key is pressed.
     * @return True if the s key is pressed, false otherwise.
     */
    static bool isSKeyDown();

    /**
     * Check if the 1 key is pressed.
     * @return True if the 1 key is pressed, false otherwise.
     */
    static bool is1KeyDown();

    /**
     * Check if the 2 key is pressed.
     * @return True if the 2 key is pressed, false otherwise.
     */
    static bool is2KeyDown();

    /**
     * Check if the 3 key is pressed.
     * @return True if the 3 key is pressed, false otherwise.
     */
    static bool is3KeyDown();

    /**
     * Check if the 4 key is pressed.
     * @return True if the 4 key is pressed, false otherwise.
     */
    static bool is4KeyDown();

    /**
     * Check if the 5 key is pressed.
     * @return True if the 5 key is pressed, false otherwise.
     */
    static bool is5KeyDown();

    /**
     * Get the mouse click position.
     * @return A vector of floats representing the x and y position of the mouse click.
     */
    static std::vector<float> GetMouseClickPosition();

    /**
     * Get the mouse position.
     * @return A vector of floats representing the x and y position of the mouse.
     */
    static std::vector<float> GetMousePosition();

    /**
     * Check if the quit button is clicked.
     * @return True if the quit button is clicked, false otherwise.
     */
    static bool isQuitClicked();
};