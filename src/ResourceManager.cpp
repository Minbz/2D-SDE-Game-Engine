#include "ResourceManager.hpp"

std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer *renderer, SDL_Surface *pixels)
{
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(renderer, pixels);
    if (nullptr == pTexture)
    {
        SDL_Log("Error creating texture: %s", SDL_GetError());
    }
    // A custom deleter is needed because type SDL_Texture is created with a call to SDL_CreateTextureFromSurface,
    // - other than the default new operator
    // Also note that here we're using the shared_ptr constructor that takes a pointer and a custom deleter,
    // - not the make_shared function which doesn't allow for custom deleters
    return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter()); // Custom deleter
}