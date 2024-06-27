#include "TextureComponent.hpp"
#include "ResourceManager.hpp"
#include "GameEntity.hpp"

// Empty constructor so that we can create an empty sprite without any properties
TextureComponent::TextureComponent()
{
}

void TextureComponent::CreateTextureComponent(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath)
{
    auto renderer = game->getSDLRenderer();
    // explicit call with std::launch::async to load the texture in a separate thread
    // start load texture when the object is created, then the texture will be gotten when it's needed for rendering after
    futureTexture = std::async(std::launch::async, [renderer, filepath]() -> std::shared_ptr<SDL_Texture>
                               { return ResourceManager::Instance().LoadTexture(renderer, filepath); });
}

TextureComponent::~TextureComponent()
{
}

ComponentType TextureComponent::GetType()
{
    return ComponentType::TextureComponent;
}

void TextureComponent::Input(float deltaTime)
{
}

void TextureComponent::Update(float deltaTime)
{
}

void TextureComponent::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
    auto renderer = game->getSDLRenderer();
    auto ge = GetGameEntity();
    auto rect = ge->GetTransform()->GetRect();

    if (nullptr == mTexture)
    {
        if (futureTexture.valid())
        {
            mTexture = futureTexture.get();
        }
        else
        {
            SDL_RenderRect(renderer, &rect);
            return;
        }
    }
    SDL_RenderTexture(renderer, mTexture.get(), nullptr, &rect);
}