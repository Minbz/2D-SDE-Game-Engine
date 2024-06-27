#include "SingleAnimation.hpp"
#include "ResourceManager.hpp"
#include "GameEntity.hpp"

// Empty constructor so that we can create an empty sprite without any properties
SingleAnimation::SingleAnimation()
{
}

void SingleAnimation::CreateAnimation(std::shared_ptr<SDLGraphicsProgram> game, std::string filepath)
{
    auto renderer = game->getSDLRenderer();
    // explicit call with std::launch::async to load the texture in a separate thread
    // start load texture when the object is created, then the texture will be gotten when it's needed for rendering after
    futureTexture = std::async(std::launch::async, [renderer, filepath]() -> std::shared_ptr<SDL_Texture>
                               { return ResourceManager::Instance().LoadTexture(renderer, filepath); });
}

SingleAnimation::~SingleAnimation()
{
}

void SingleAnimation::SetFrameConfig(int x, int y, int w, int w_offset, int h, int maxFrame, int millisecond_duration, bool repeat)
{
    initialX = x;
    offsetW = w_offset;
    mRect_src.x = x;
    mRect_src.y = y;
    mRect_src.w = w;
    mRect_src.h = h;
    mMaxFrame = maxFrame;
    mFrameDuration = millisecond_duration;
    mRepeat = repeat;
}

int SingleAnimation::GetW() const
{
    return mRect_src.w;
}

int SingleAnimation::GetH() const
{
    return mRect_src.h;
}

int SingleAnimation::GetDuration()
{
    return mFrameDuration;
}

void SingleAnimation::ResetFrame()
{
    currFrame = -1;
    mRect_src.x = initialX;
}

void SingleAnimation::UpdateFrame()
{
    if (frameStartTime != 0.0f)
    {
        if (SDL_GetTicks() - frameStartTime < mFrameDuration)
        {
            return;
        }
        else
        {
            currFrame++;
            if (currFrame >= mMaxFrame)
            {
                if (mRepeat)
                    currFrame = 0;
                else
                    currFrame = mMaxFrame - 1;
            }
            // Switch Frame
            mRect_src.x = initialX + (mRect_src.w + offsetW) * currFrame;
        }
    }
    frameStartTime = SDL_GetTicks();
}

void SingleAnimation::RenderFrame(std::shared_ptr<SDLGraphicsProgram> game, std::shared_ptr<GameEntity> ge)
{
    auto renderer = game->getSDLRenderer();
    auto rect_dest = ge->GetTransform()->GetRect();
    SDL_FlipMode isFlipped = SDL_FLIP_NONE;
    if (ge->GetFlip())
    {
        isFlipped = SDL_FLIP_HORIZONTAL;
    }

    if (nullptr == mTexture)
    {
        if (futureTexture.valid())
        {
            mTexture = futureTexture.get();
        }
        else
        {
            SDL_RenderRect(renderer, &rect_dest);
            return;
        }
    }
    SDL_RenderTextureRotated(renderer, mTexture.get(), &mRect_src, &rect_dest, 0, nullptr, isFlipped);
}
