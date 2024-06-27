#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include "ComponentType.hpp"
#include "SDLGraphicsProgram.hpp"

// Forward declaration of GameEntity which is included in our Component
struct GameEntity;

/**
 * A base component that is attached to a GameEntity.
 * Other components inherit from this class.
 * @see GameEntity
 * @see ComponentType
 */
struct Component
{
    /**
     * Constructor for Component.
     */
    Component()
    {
    }

    /**
     * Destructor for Component.
     * Pure virtual function so that derived classes must override it.
     */
    virtual ~Component()
    {
    }

    /**
     * Input function for the component.
     * Pure virtual function so that derived classes must override it.
     * @param deltaTime The time since the last input.
     */
    virtual void Input(float deltaTime)
    {
    }

    /**
     * Update function for the component.
     * Pure virtual function so that derived classes must override it.
     * @param deltaTime The time since the last update.
     */
    virtual void Update(float deltaTime)
    {
    }

    /**
     * Render function for the component.
     * Pure virtual function so that derived classes must override it.
     * @param game The game to render to as an SDLGraphicsProgram.
     * @see SDLGraphicsProgram
     */
    virtual void Render(std::shared_ptr<SDLGraphicsProgram> game)
    {
    }

    /**
     * Returns the type of the component.
     * Pure virtual function so that derived classes must override it.
     * @return The type of the component.
     * @see ComponentType
     */
    virtual ComponentType GetType() = 0;

    /**
     * Set the GameEntity that the component is associated with.
     * @param g The GameEntity to set.
     * @see GameEntity
     */
    void SetGameEntity(std::shared_ptr<GameEntity> g)
    {
        mGameEntity = g;
    }

    /**
     * Get the GameEntity that the component is associated with.
     * @return The GameEntity that the component is associated with.
     * @see GameEntity
     */
    std::shared_ptr<GameEntity> GetGameEntity()
    {
        return mGameEntity;
    }

    // Some things to think about -- component communication
    // void send(int message){}
    // void receive(int message){}
private:
    /**
     * The GameEntity that the component is associated with.
     * @see GameEntity
     */
    std::shared_ptr<GameEntity> mGameEntity;
};