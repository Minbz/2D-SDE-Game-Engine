#include "AnimationComponent.hpp"
#include "SingleAnimation.hpp"

// Empty constructor so that we can create an empty sprite without any properties
AnimationComponent::AnimationComponent()
{
}

AnimationComponent::~AnimationComponent()
{
}

ComponentType AnimationComponent::GetType()
{
    return ComponentType::AnimationComponent;
}

void AnimationComponent::AddAnimation(std::string state, std::shared_ptr<SingleAnimation> a)
{
    mAnimations[state] = a;
}

std::shared_ptr<SingleAnimation> AnimationComponent::GetAnimation(std::string state)
{
    return mAnimations[state];
}

void AnimationComponent::Input(float deltaTime)
{
}

void AnimationComponent::Update(float deltaTime)
{
    auto ge = GetGameEntity();
    auto state = ge->GetState();

    auto found = mAnimations.find(state);
    if (found == mAnimations.end())
    {
        SDL_Log("ERROR: The Animation does not exist in this GameEntity.");
        return;
    }

    if (!currState.empty() && currState != state)
    {
        mAnimations[currState]->ResetFrame();
    }
    currState = state;
    mAnimations[state]->UpdateFrame();
}

void AnimationComponent::Render(std::shared_ptr<SDLGraphicsProgram> game)
{
    if (currState.empty())
    {
        return;
    }

    auto renderer = game->getSDLRenderer();
    auto ge = GetGameEntity();

    mAnimations[currState]->RenderFrame(game, ge);
}