#include "Collision2DComponent.hpp"

// Empty constructor so that we can create an empty sprite without any properties
Collision2DComponent::Collision2DComponent()
{
}

Collision2DComponent::~Collision2DComponent()
{
}

ComponentType Collision2DComponent::GetType()
{
    return ComponentType::Collision2DComponent;
}

void Collision2DComponent::Input(float deltaTime)
{
}

void Collision2DComponent::Update(float deltaTime)
{
}

void Collision2DComponent::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
}

void Collision2DComponent::SetWidth(float w)
{
    mRectangle.w = w;
}

void Collision2DComponent::SetHeight(float h)
{
    mRectangle.h = h;
}

void Collision2DComponent::SetWH(float w, float h)
{
    mRectangle.w = w;
    mRectangle.h = h;
}

float Collision2DComponent::GetWidth() const
{
    return mRectangle.w;
}

float Collision2DComponent::GetHeight() const
{
    return mRectangle.h;
}

void Collision2DComponent::SetX(float x)
{
    mRectangle.x = x;
}

void Collision2DComponent::SetY(float y)
{
    mRectangle.y = y;
}

void Collision2DComponent::SetXY(float x, float y)
{
    mRectangle.x = x;
    mRectangle.y = y;
}

float Collision2DComponent::GetX() const
{
    return mRectangle.x;
}

float Collision2DComponent::GetY() const
{
    return mRectangle.y;
}

SDL_FRect Collision2DComponent::GetRect() const
{
    return mRectangle;
}