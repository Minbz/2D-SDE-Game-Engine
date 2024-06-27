#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <mutex>

/**
 * Functor to be used as a custom deleter when creating the shared pointer.
 * This functor will be used to destroy the SDL_Texture when the shared pointer goes out of scope.
 */
struct TextureFunctorDeleter
{
    /**
     * Overloaded function call operator to destroy the SDL_Texture.
     * @param pTexture The SDL_Texture to destroy.
     */
    void operator()(SDL_Texture *pTexture) const
    {
        SDL_DestroyTexture(pTexture);
    }
};

// Function declaration to create a shared pointer to a texture
std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer *renderer, SDL_Surface *pixels);

/**
 * A singleton class that manages the resources of the game.
 * This class is responsible for loading and storing textures.
 */
struct ResourceManager
{
    /**
     * Used to get the singleton instance of the ResourceManager.
     * If the instance does not exist, it will be created.
     */
    static ResourceManager &Instance() // Just like *, here the & is used to return a reference of ReserouceManager type to the object
    {
        if (nullptr == mInstance)
        {
            mInstance = new ResourceManager();
        }
        return *mInstance; // De-referencing the pointer to get the object since we're returning a reference
    }

    /**
     * Load a texture from a file.
     * If the texture has already been loaded, it will be reused.
     * @param renderer The renderer to use to create the texture.
     * @param filepath The path to the texture file.
     * @return A shared pointer to the texture.
     */
    std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer *renderer, std::string filepath)
    // Changed from const char* to std::string for better key uniqueness than const char* which eveually is a pointer of address
    {
        std::lock_guard<std::mutex> lock(mMutex); //!< Lock the mutex to prevent from multiple threads accessing the resource at the same time

        /** C++ 20 just uses contains method
         * If don't have C++ 20, use find method:
         * - if(mTextureResources.find(filepath) != mTextureResources.end()）{...}
         */
        if (!mTextureResources.contains(filepath))
        {
            SDL_Surface *pixels = SDL_LoadBMP(filepath.c_str()); //!< Changed from std::string to const char* for SDL_LoadBMP

            /**
             *  Get rid of the background
             */
            SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

            std::shared_ptr<SDL_Texture> texture = make_shared_texture(renderer, pixels);
            mTextureResources.insert({filepath, texture});

            SDL_DestroySurface(pixels);
            SDL_Log("Created new resource %s", filepath.c_str());
        }
        // else
        // {
        //     SDL_Log("Reused resource %s", filepath.c_str());
        // }

        return mTextureResources[filepath];
    }

private:
    /**
     * Mutex to prevent multiple threads from accessing the resources at the same time.
     */
    std::mutex mMutex;
    /**
     * The color key - r to use when loading textures.
     */
    int COLOR_KEY_R = 0;
    /**
     * The color key - g to use when loading textures.
     */
    int COLOR_KEY_G = 0;
    /**
     * The color key - b to use when loading textures.
     */
    int COLOR_KEY_B = 0;

    /**
     * Private Constructor for ResourceManager.
     * This is a singleton class so the constructor is private.
     */
    ResourceManager()
    {
    }

    // inline is sort of easier to deal with, though it's exposing some info
    /**
     * The singleton instance of the ResourceManager.
     */
    inline static ResourceManager *mInstance{nullptr};

    /**
     * A map of the texture resources.
     * The key is the filepath of the texture.
     * The value is a shared pointer to the texture.
     */
    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> mTextureResources;
};
