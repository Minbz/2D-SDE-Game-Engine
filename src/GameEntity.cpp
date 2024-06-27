#include "GameEntity.hpp"
#include "ResourceManager.hpp"

GameEntity::GameEntity()
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::Update(float deltaTime)
{
    for (auto &[key, value] : mComponents)
    {
        mComponents[key]->Update(deltaTime);
    }
}

void GameEntity::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
    for (auto &[key, value] : mComponents)
    {
        mComponents[key]->Render(game);
    }
}

template <typename T>
void GameEntity::AddComponent(std::shared_ptr<T> c)
{
    // Could use the tempalte information to get the exact component type
    mComponents[c->GetType()] = c;
    c->SetGameEntity(shared_from_this());
}

void GameEntity::AddTransform(float x, float y, float width, float height)
{
    std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>();
    transform->SetXY(x, y);
    transform->SetWH(width, height);
    AddComponent<TransformComponent>(transform);
}

void GameEntity::AddTexture(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath)
{
    auto renderer = game->getSDLRenderer();
    std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
    texture->CreateTextureComponent(game, filepath);
    AddComponent<TextureComponent>(texture);
}

void GameEntity::AddCollision2D(float x, float y, float width, float height)
{
    std::shared_ptr<Collision2DComponent> collision = std::make_shared<Collision2DComponent>();
    collision->SetXY(x, y);
    collision->SetWH(width, height);
    AddComponent<Collision2DComponent>(collision);
}

void GameEntity::AddAnimation(std::string state, std::shared_ptr<SingleAnimation> a)
{
    auto anim = GetComponent<AnimationComponent>(ComponentType::AnimationComponent);
    if (anim == nullptr)
    {
        anim = std::make_shared<AnimationComponent>();
        AddComponent<AnimationComponent>(anim);
        SDL_Log("Adding AnimationComponent to GameEntity");
    }
    anim->AddAnimation(state, a);
}

template <typename T>
std::shared_ptr<T> GameEntity::GetComponent(ComponentType type)
{
    auto found = mComponents.find(type);
    if (found != mComponents.end())
    {
        return dynamic_pointer_cast<T>(found->second);
    }
    // For now -- our way of handling a component that does not exist.
    // Note: It might be useful to 'log' this as an error
    // Note: Exception could be used here -- with caution
    // SDL_Log("ERROR: The Component does not exist in this GameEntity. Returning nullptr (This might segfault).");
    return nullptr;
}

std::shared_ptr<TransformComponent> GameEntity::GetTransform()
{
    return GetComponent<TransformComponent>(ComponentType::TransformComponent);
}

std::shared_ptr<Collision2DComponent> GameEntity::GetCollision2D()
{
    return GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
}

std::shared_ptr<AnimationComponent> GameEntity::GetAnimations()
{
    return GetComponent<AnimationComponent>(ComponentType::AnimationComponent);
}

std::shared_ptr<TextureComponent> GameEntity::GetTexture()
{
    return GetComponent<TextureComponent>(ComponentType::TextureComponent);
}

bool GameEntity::isCollidingWith(std::shared_ptr<GameEntity> s)
{
    if (!isCollidable() || !s->isCollidable())
    {
        return false;
    }

    auto source = s->GetCollision2D()->GetRect();
    auto us = GetCollision2D()->GetRect();

    SDL_FRect result;
    return SDL_GetRectIntersectionFloat(&source, &us, &result);
}

bool GameEntity::isCollidable()
{
    return GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent) != nullptr;
}

void GameEntity::SetName(std::string name)
{
    mName = name;
}

std::string GameEntity::GetName() const
{
    return mName;
}

void GameEntity::SetState(std::string s)
{
    mState = s;
}

std::string GameEntity::GetState() const
{
    return mState;
}

void GameEntity::SetFlip(bool flip)
{
    mFlip = flip;
}

bool GameEntity::GetFlip() const
{
    return mFlip;
}

void GameEntity::MoveX(float x)
{
    auto transform = GetTransform();
    transform->SetX(transform->GetX() + x);

    auto collider = GetCollision2D();
    collider->SetX(collider->GetX() + x);
}

void GameEntity::MoveY(float y)
{
    auto transform = GetTransform();
    transform->SetY(transform->GetY() + y);

    auto collider = GetCollision2D();
    collider->SetY(collider->GetY() + y);
}

// Explicit template instantiations
// template void GameEntity::AddComponent<TextureComponent>(std::shared_ptr<TextureComponent> C);
// template void GameEntity::AddComponent<TransformComponent>(std::shared_ptr<TransformComponent> C);
// template void GameEntity::AddComponent<Collision2DComponent>(std::shared_ptr<Collision2DComponent> C);

// template std::shared_ptr<TextureComponent> GameEntity::GetComponent<TextureComponent>(ComponentType type);
// template std::shared_ptr<TransformComponent> GameEntity::GetComponent<TransformComponent>(ComponentType type);
// template std::shared_ptr<Collision2DComponent> GameEntity::GetComponent<Collision2DComponent>(ComponentType type);