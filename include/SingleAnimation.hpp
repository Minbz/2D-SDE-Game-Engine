#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include "SDLGraphicsProgram.hpp"
#include "GameEntity.hpp"

// Animation is not a component as one object could have multiple animations
/**
 * A struct that represents a single animation.
 * Note that this is not a component.
 * Used to create and render a single animation to be held by an AnimationComponent.
 * @see AnimationComponent
 */
struct SingleAnimation
{
    /**
     * Constructor for SingleAnimation.
     * Note that the texture is not loaded here. It is loaded in CreateAnimation.
     * @see CreateAnimation
     */
    SingleAnimation();

    /**
     * Create an animation from a file.
     * To speed up the loading process, the texture is loaded in a separate thread.
     * Note that the configuration of the frame must be set after the texture is loaded.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @param filepath The path to the file to load.
     * @see SetFrameConfig
     */
    void CreateAnimation(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath);

    /**
     * Destructor for SingleAnimation.
     */
    ~SingleAnimation();

    /**
     * Set the configuration of the frame.
     * @param x The x position of the frame.
     * @param y The y position of the frame.
     * @param w The width of the frame.
     * @param w_offset The offset of the width of the frame.
     * @param h The height of the frame.
     * @param maxFrame The maximum number of frames.
     * @param millisecond_duration The duration of the frame in milliseconds.
     * @param repeat Whether the animation should repeat.
     */
    void SetFrameConfig(int x, int y, int w, int w_offset, int h, int maxFrame, int millisecond_duration, bool repeat);

    /**
     * Get the width of the frame.
     * @return The width of the frame.
     */
    int GetW() const;

    /**
     * Get the height of the frame.
     * @return The height of the frame.
     */
    int GetH() const;

    /**
     * Get the duration of the frame.
     * @return The duration of the frame.
     */
    int GetDuration();

    /**
     * Reset the frame to the initial frame.
     */
    void ResetFrame();

    /**
     * Update the frame.
     * Only updates the frame if the duration of the frame has passed.
     * When the last frame is reached, the frame is reset if the animation is set to repeat.
     * @see GetDuration
     */
    void UpdateFrame();

    /**
     * Render the frame.
     * Frame will be flipped if the associated game entity's mFlip is set to true.
     * If no texture is set, only the source rectangle will be rendered.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @param ge The GameEntity to render the frame to.
     */
    void RenderFrame(std::shared_ptr<SDLGraphicsProgram> game, std::shared_ptr<GameEntity> ge);

private:
    /**
     * The future for the texture.
     * Used to load the texture in a separate thread.
     */
    std::future<std::shared_ptr<SDL_Texture>> futureTexture;
    /**
     * The texture of the animation.
     */
    std::shared_ptr<SDL_Texture> mTexture;
    /**
     * The source rectangle of the frame.
     */
    SDL_FRect mRect_src{0.0f, 0.0f, 0.0f, 0.0f};
    /**
     * The x position of the initial frame.
     */
    int initialX;
    /**
     * The offset of the width of the frame.
     */
    int offsetW;
    /**
     * The maximum number of frames.
     */
    int mMaxFrame;
    /**
     * The duration of each frame in milliseconds.
     */
    int mFrameDuration;
    /**
     * The current frame.
     */
    int currFrame = -1;
    /**
     * The start time of the frame.
     * Used to calculate the duration of the frame.
     */
    float frameStartTime{0.0f};
    /**
     * Whether the animation should repeat.
     */
    bool mRepeat;
};