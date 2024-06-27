#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

#include "Component.hpp"

// Forward declaration of SingleAnimation
struct SingleAnimation;
/**
 * A component that handles the animations of an entity.
 * Inherited from Component.
 * @see Component
 */
struct AnimationComponent : public Component
{
    /**
     * Constructor for AnimationComponent.
     */
    AnimationComponent();

    /**
     * Destructor for AnimationComponent.
     */
    ~AnimationComponent();

    /**
     * Returns the type of the component.
     * @return The type of the component.
     * @see ComponentType
     */
    ComponentType GetType() override;

    /**
     * Adds an animation to the component.
     * @param state The state of the animation. Used to identify the animation.
     * @param a The animation to add.
     * @see SingleAnimation
     */
    void AddAnimation(std::string state, std::shared_ptr<SingleAnimation> a);

    /**
     * Sets the current state of the animation.
     * @param state The state to set.
     * @see SingleAnimation
     */
    std::shared_ptr<SingleAnimation> GetAnimation(std::string state);

    /**
     * Inherited from Component. Not used in this component.
     * @param deltaTime The time since the last input.
     * @see Component
     */
    void Input(float deltaTime) override;

    /**
     * Choose the correct animation to play based on the state of the entity.
     * Update the frame of the chosen animation.
     * If the state has changed, reset the frame of the previously used animation before updating the new one.
     * @param deltaTime The time since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * Render the current frame of the chosen animation.
     * @param game The game to render the animation on as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     */
    void Render(std::shared_ptr<SDLGraphicsProgram> game) override;

private:
    /**
     * The current state of the animation.
     * Used to identify the current animation.
     */
    std::string currState;
    /**
     * A map of all the animations in the component.
     * The key is the state of the animation as a string.
     * The value is the animation as a SingleAnimation.
     * @see SingleAnimation
     */
    std::unordered_map<std::string, std::shared_ptr<SingleAnimation>> mAnimations;
};