#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include "Component.hpp"

/**
 * A component that handles the 2D collision of an entity.
 * It is used to detect collisions between entities, could be different from the transform of an entity.
 * Inherited from Component.
 * @see Component
 * @see TransformComponent
 */
struct Collision2DComponent : public Component
{
    /**
     * Constructor for Collision2DComponent.
     * Note that the rectangle is initialized to 0, 0, 0, 0 when created.
     * The width and height of the rectangle should be set using Setter functions before using the component.
     * @see SetWidth
     * @see SetHeight
     * @see SetWH
     */
    Collision2DComponent();

    /**
     * Destructor for Collision2DComponent.
     */
    ~Collision2DComponent();

    /**
     * Returns the type of the component.
     * @return The type of the component.
     * @see ComponentType
     */
    ComponentType GetType() override;

    /**
     * Inherited from Component. Not used in this component.
     * @param deltaTime The time since the last input.
     * @see Component
     */
    void Input(float deltaTime) override;

    /**
     * Inherited from Component. Not used in this component.
     * @param deltaTime The time since the last update.
     * @see Component
     */
    void Update(float deltaTime) override;

    /**
     * Inherited from Component. Not used in this component.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     * @see Component
     */
    void Render(std::shared_ptr<SDLGraphicsProgram> game) override;

    /**
     * Set the width of the collision box.
     * @param w The width to set.
     */
    void SetWidth(float w);

    /**
     * Set the height of the collision box.
     * @param h The height to set.
     */
    void SetHeight(float h);

    /**
     * Set the width and height of the collision box.
     * @param w The width to set.
     * @param h The height to set.
     */
    void SetWH(float w, float h);

    /**
     * Get the width of the collision box.
     * @return The width of the collision box.
     */
    float GetWidth() const;

    /**
     * Get the height of the collision box.
     * @return The height of the collision box.
     */
    float GetHeight() const;

    /**
     * Set the x position of the collision box.
     * @param x The x position to set.
     */
    void SetX(float x);

    /**
     * Set the y position of the collision box.
     * @param y The y position to set.
     */
    void SetY(float y);

    /**
     * Set the x and y position of the collision box.
     * @param x The x position to set.
     * @param y The y position to set.
     */
    void SetXY(float x, float y);

    /**
     * Get the x position of the collision box.
     * @return The x position of the collision box.
     */
    float GetX() const;

    /**
     * Get the y position of the collision box.
     * @return The y position of the collision box.
     */
    float GetY() const;

    /**
     * Get the collision box as an SDL_FRect.
     * @return The collision box as an SDL_FRect.
     */
    SDL_FRect GetRect() const;

private:
    /**
     * The rectangle that represents the collision box.
     * Primarily used for 2D collision detection.
     */
    SDL_FRect mRectangle{0.0f, 0.0f, 0.0f, 0.0f};
};