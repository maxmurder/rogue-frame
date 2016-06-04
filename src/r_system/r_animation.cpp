#include "r_animation.h"

void AnimationSystem::AddAnimation(EntityID id, std::string name, std::vector<SDL_Rect> frames)
{
    if(GetEntity(id) != NULL)
    {
       components[id]->animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, frames) );
    }
}

void AnimationSystem::SetAnimation(EntityID id, std::string animation)
{
     if(GetEntity(id) != NULL)
    {
        if (components[id]->animations.find(animation) == components[id]->animations.end() )
        {
            std::cout << "Animation: " << animation << " not found in list." << std::endl;
        }else
        {
            components[id]->currentAnimation = animation;
        }
    }
}

void AnimationSystem::SetFrame(EntityID id, uint32_t frame)
{
    if(GetEntity(id) != NULL)
    {
        components[id]->currentFrame = frame;
    }
}

SDL_Rect AnimationSystem::GetCurrentFrame(EntityID id)
{
    SDL_Rect f;
    if(GetEntity(id) != NULL)
    {
        if(!components[id]->animations.empty())
        {
            if (components[id]->animations.find(components[id]->currentAnimation) == components[id]->animations.end() )
            {
            }else
            {
                if(components[id]->currentFrame < components[id]->animations[components[id]->currentAnimation].size())
                {
                    f = components[id]->animations[components[id]->currentAnimation][components[id]->currentFrame];
                }
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
