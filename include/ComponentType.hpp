#pragma once

/**
 * An enum class that represents the type of a component.
 * Used to identify the type of a component.
 * @see Component
 * @see TextureComponent
 * @see TransformComponent
 * @see Collision2DComponent
 * @see AnimationComponent
 */
enum class ComponentType : short
{
    TextureComponent,
    TransformComponent,
    Collision2DComponent,
    AnimationComponent,
};
