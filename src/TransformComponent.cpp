#include "TransformComponent.hpp"

// Empty constructor so that we can create an empty sprite without any properties
TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

ComponentType TransformComponent::GetType()
{
    return ComponentType::TransformComponent;
}

void TransformComponent::Input(float deltaTime)
{
}

void TransformComponent::Update(float deltaTime)
{
}

void TransformComponent::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
}

void TransformComponent::SetWidth(float w)
{
    mRectangle.w = w;
}

void TransformComponent::SetHeight(float h)
{
    mRectangle.h = h;
}

void TransformComponent::SetWH(float w, float h)
{
    mRectangle.w = w;
    mRectangle.h = h;
}

float TransformComponent::GetWidth() const
{
    return mRectangle.w;
}

float TransformComponent::GetHeight() const
{
    return mRectangle.h;
}

void TransformComponent::SetX(float x)
{
    mRectangle.x = x;
}

void TransformComponent::SetY(float y)
{
    mRectangle.y = y;
}

void TransformComponent::SetXY(float x, float y)
{
    mRectangle.x = x;
    mRectangle.y = y;
}

float TransformComponent::GetX() const
{
    return mRectangle.x;
}

float TransformComponent::GetY() const
{
    return mRectangle.y;
}

SDL_FRect TransformComponent::GetRect() const
{
    return mRectangle;
}