#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <future>

#include "Component.hpp"

/**
 * A component that handles the texture of an entity.
 * Inherited from Component.
 * Different from AnimationComponent in that it only handles a single texture.
 * @see Component
 * @see AnimationComponent
 */
struct TextureComponent : public Component
{
    /**
     * Constructor for TextureComponent.
     * Note that the texture is not created until CreateTextureComponent is called.
     */
    TextureComponent();

    /**
     * Create a texture component from a filepath.
     * To speed up the loading process, the texture is loaded in a separate thread.
     * @param game The game to create the texture in as an SDLGraphicsProgram.
     * @param filepath The filepath of the image to create the texture from.
     */
    void CreateTextureComponent(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath);

    /**
     * Destructor for TextureComponent.
     */
    ~TextureComponent();

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
     * Render the texture to the screen.
     * If no texture is set, only the source rectangle will be rendered.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     * @see Component
     */
    void Render(std::shared_ptr<SDLGraphicsProgram> game) override;

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
};