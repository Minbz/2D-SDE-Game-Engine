#pragma once

#include <SDL3/SDL.h>
#include <memory>

#include "Component.hpp"

/**
 * A component that handles the transform of an entity.
 * The texture or animation of an entity is rendered based on the transform.
 * Inherited from Component.
 * @see Component
 * @see TextureComponent
 * @see SingleAnimation
 * @see Collision2DComponent
 */
struct TransformComponent : public Component
{
    /**
     * Constructor for TransformComponent.
     * Note that the rectangle is initialized to 0, 0, 0, 0 when created.
     * The width and height of the rectangle should be set using Setter functions before using the component.
     * @see SetWidth
     * @see SetHeight
     * @see SetWH
     */
    TransformComponent();

    /**
     * Destructor for TransformComponent.
     */
    ~TransformComponent();

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
     * Set the width of the rectangle.
     * @param w The width to set.
     */
    void SetWidth(float w);

    /**
     * Set the height of the rectangle.
     * @param h The height to set.
     */
    void SetHeight(float h);

    /**
     * Set the width and height of the rectangle.
     * @param w The width to set.
     * @param h The height to set.
     */
    void SetWH(float w, float h);

    /**
     * Get the width of the rectangle.
     * @return The width of the rectangle.
     */
    float GetWidth() const;

    /**
     * Get the height of the rectangle.
     * @return The height of the rectangle.
     */
    float GetHeight() const;

    /**
     * Set the x position of the rectangle.
     * @param x The x position to set.
     */
    void SetX(float x);

    /**
     * Set the y position of the rectangle.
     * @param y The y position to set.
     */
    void SetY(float y);

    /**
     * Set the x and y position of the rectangle.
     * @param x The x position to set.
     * @param y The y position to set.
     */
    void SetXY(float x, float y);

    /**
     * Get the x position of the rectangle.
     * @return The x position of the rectangle.
     */
    float GetX() const;

    /**
     * Get the y position of the rectangle.
     * @return The y position of the rectangle.
     */
    float GetY() const;

    /**
     * Get the rectangle representing the transform as an SDL_FRect.
     * @return The rectangle as an SDL_FRect.
     */
    SDL_FRect GetRect() const;

private:
    /**
     * The rectangle representing the transform.
     * Primarily used for rendering.
     */
    SDL_FRect mRectangle{0.0f, 0.0f, 0.0f, 0.0f};
};