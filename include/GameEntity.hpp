#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

#include "SDLGraphicsProgram.hpp"
#include "Component.hpp"
#include "TextureComponent.hpp"
#include "TransformComponent.hpp"
#include "Collision2DComponent.hpp"
#include "AnimationComponent.hpp"
#include "SingleAnimation.hpp"

/**
 * A struct that represents a GameEntity.
 * A GameEntity is an object in the game that has component(s) attached to it.
 * @see Component
 * @see ComponentType
 */
struct GameEntity : public std::enable_shared_from_this<GameEntity>
{
    /**
     * Constructor for GameEntity.
     * Empty constructor so that we can create a GameEntity without any components.
     */
    GameEntity();

    /**
     * Destructor for GameEntity.
     */
    ~GameEntity();

    /**
     * Update function for the entity.
     * Calls the update function for each component attached to the entity.
     * @param deltaTime The time since the last update.
     */
    void Update(float deltaTime);

    /**
     * Render function for the entity.
     * Calls the render function for each component attached to the entity.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     */
    void Render(std::shared_ptr<SDLGraphicsProgram> game);

    /**
     * Add a component to the entity.
     * @param c The component to add.
     * @tparam T The type of the component.
     * @see ComponentType
     */
    template <typename T>
    void AddComponent(std::shared_ptr<T> c);

    /**
     * Add a transform component to the entity.
     * Short hand for creating a transform component and adding it to the entity.
     * @param x The x position of the entity.
     * @param y The y position of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    void AddTransform(float x, float y, float width, float height);

    /**
     * Add a texture component to the entity.
     * Short hand for creating a texture component and adding it to the entity.
     * @param game The game to render the texture on as an SDLGraphicsProgram.
     * @param filepath The filepath of the texture to load.
     * @see SDLGraphicsProgram
     */
    void AddTexture(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath);

    /**
     * Add a 2D collision component to the entity.
     * Short hand for creating a 2D collision component and adding it to the entity.
     * @param x The x position of the entity.
     * @param y The y position of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    void AddCollision2D(float x, float y, float width, float height);

    /**
     * Add a single animation to the entity.
     * If the entity does not have an animation component, one will be created to hold the single animation.
     * @param state The state of the animation. Used to identify the animation.
     * @param a The animation to add.
     * @see SingleAnimation
     */
    void AddAnimation(std::string state, std::shared_ptr<SingleAnimation> a);

    /**
     * Get a component from the entity.
     * @param type The type of the component to get.
     * @tparam T The type of the component.
     * @return The component of the specified type.
     * @see ComponentType
     */
    template <typename T>
    std::shared_ptr<T> GetComponent(ComponentType type);

    /**
     * Get the transform component of the entity.
     * Short hand for getting the transform component from the entity.
     * @return The transform component of the entity.
     */
    std::shared_ptr<TransformComponent> GetTransform();

    /**
     * Get the 2D collision component of the entity.
     * Short hand for getting the 2D collision component from the entity.
     * @return The 2D collision component of the entity.
     */
    std::shared_ptr<Collision2DComponent> GetCollision2D();

    /**
     * Get the animation component of the entity.
     * Short hand for getting the animation component from the entity.
     * @return The animation component of the entity.
     */
    std::shared_ptr<AnimationComponent> GetAnimations();

    /**
     * Get the texture component of the entity.
     * Short hand for getting the texture component from the entity.
     * @return The texture component of the entity.
     */
    std::shared_ptr<TextureComponent> GetTexture();

    /**
     * Check if the entity is colliding with another entity.
     * @param s The entity to check for collision with.
     * @return True if the entities are colliding, false otherwise.
     */
    bool isCollidingWith(std::shared_ptr<GameEntity> s);

    /**
     * Check if the entity is collidable by checking if it has a collision component.
     * If the entity has a collision component, it is collidable.
     * @return True if the entity is collidable, false otherwise.
     */
    bool isCollidable();

    /**
     * Set the name of the entity.
     * Used to identify the entity.
     * @param name The name to set.
     */
    void SetName(std::string name);

    /**
     * Get the name of the entity.
     * Used to identify the entity.
     * @return The name of the entity.
     */
    std::string GetName() const;

    /**
     * Set the state of the entity.
     * Used to identify which animation to play.
     * @param s The state to set.
     */
    void SetState(std::string s);

    /**
     * Get the state of the entity.
     * Used to identify which animation to play.
     * @return The state of the entity.
     */
    std::string GetState() const;

    /**
     * Set the flip of the entity.
     * Used to flip the entity's animation horizontally.
     * @param flip The flip to set.
     */
    void SetFlip(bool flip);

    /**
     * Get the flip of the entity.
     * Used to identify if the entity's animation is flipped horizontally.
     * @return The flip of the entity.
     */
    bool GetFlip() const;

    /**
     * Move the entity in the x direction, both in the transform component and the collision component.
     * Different from the transform component's move function.
     * This function moves the entity's position by the specified amount for each frame.
     * @param x The amount to move in the x direction.
     * @see TransformComponent::MoveX
     *
     */
    void MoveX(float x);

    /**
     * Move the entity in the y direction, both in the transform component and the collision component.
     * Different from the transform component's move function.
     * This function moves the entity's position by the specified amount for each frame.
     * @param y The amount to move in the y direction.
     * @see TransformComponent::MoveY
     */
    void MoveY(float y);

private:
    /**
     * The components attached to the entity.
     * A map of component type to component.
     * Key is the type of the component.
     * Value is the component.
     * @see Component
     * @see ComponentType
     */
    std::unordered_map<ComponentType, std::shared_ptr<Component>> mComponents;
    /**
     * The name of the entity.
     * Used to identify the entity.
     */
    std::string mName;
    /**
     * The state of the entity.
     * Used to identify which animation to play.
     */
    std::string mState;
    /**
     * The flip of the entity.
     * Used to flip the entity's animation horizontally.
     * Or to identify if the entity's animation is flipped horizontally.
     */
    bool mFlip{false};
};
