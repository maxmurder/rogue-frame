#include "r_animation.h"

using namespace std;


void AnimationComponent::AddAnimation(std::string name, std::vector<SDL_Rect> frames)
{
    animations.insert( pair<string, vector<SDL_Rect>>(name, frames) );
}

void AnimationComponent::SetAnimation(std::string animation)
{
    if (animations.find(animation) == animations.end() )
    {
        cout << "Animation: " << animation << " not found in list." << endl;
    }else
    {
        currentAnimation = animation;
    }
}

void AnimationComponent::SetFrame(uint32_t frame)
{
    currentFrame = frame;
}

SDL_Rect AnimationComponent::GetCurrentFrame()
{
    SDL_Rect f;
    if(!animations.empty())
    {
        if (animations.find(currentAnimation) == animations.end() )
        {
            cout << "Animation: " << currentAnimation << " not found in list." << endl;
        }else
        {
            if(currentFrame < animations[currentAnimation].size())
            {
                f = animations[currentAnimation][currentFrame];
            }
        }
    }
    return f;
}

void AnimationSystem::Update()
{
    for (auto &s : components)
    {
        if(s.second->animationSpeed > 0)
        {
            if(s.second->frameCount > s.second->animationSpeed)
            {   
                s.second->frameCount = 0;
                s.second->currentFrame++;
                if (s.second->currentFrame >= s.second->animations[s.second->currentAnimation].size())
                {
                    s.second->currentFrame = 0;
                }
            }
            s.second->frameCount++;
        }
    }
}
