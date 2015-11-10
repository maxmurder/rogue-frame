#include "r_sprite.h"
#include "r_renderer.h"

using namespace std;

void SpriteComponent::Init( SDL_Texture  *tex, SDL_Rect dims, SDL_Color foregroundColor, SDL_Color backgroundColor)
{
    texture = tex;
    fgColor = foregroundColor;
    bgColor = backgroundColor;
    dimensions = dims;
    visible = true;
    animations.insert(pair<string, vector<SDL_Rect>>("DEFAULT", {{0,0,dimensions.w,dimensions.h}}) );
    currentAnimation = "DEFAULT";
}

void SpriteSystem::AddComponent(EntityID ownerID, SDL_Texture  *texture, SDL_Rect dimensions, SDL_Color fgColor, SDL_Color bgColor)
{
    System::AddComponent( r_component::Create("SpriteComponent", ownerID) , ownerID);
    components[ownerID]->Init(texture, dimensions, fgColor, bgColor);
}

void SpriteSystem::AddAnimation(EntityID id, std::string name, std::vector<SDL_Rect> frames)
{
    if(GetEntity(id) != NULL)
    {
       components[id]->animations.insert(pair<string, vector<SDL_Rect>>(name, frames) );
    }
}

void SpriteSystem::SetAnimation(EntityID id, std::string animation)
{
     if(GetEntity(id) != NULL)
    {
        if (components[id]->animations.find(animation) == components[id]->animations.end() )
        {
            cout << "Animation: " << animation << " not found in list." << endl;
        }else
        {
            components[id]->currentAnimation = animation;
        }
    }
}

void SpriteSystem::SetFrame(EntityID id, uint32_t frame)
{
    if(GetEntity(id) != NULL)
    {
        components[id]->currentFrame = frame;
    }
}

SDL_Rect SpriteSystem::GetCurrentFrame(EntityID id)
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

void SpriteSystem::Update(double deltaTime)
{
    for (auto &s : components)
    {
        if(s.second->animationSpeed > 0)
        {
            if(s.second->frameTime > s.second->animationSpeed)
            {   
                s.second->frameTime = 0;
                s.second->currentFrame++;
                if (s.second->currentFrame >= s.second->animations[s.second->currentAnimation].size())
                {
                    s.second->currentFrame = 0;
                }
            }
        s.second->frameTime += deltaTime;
        }
    }
}

void SpriteSystem::Render()
{
    for (auto &s: components)
    {
        if(GetEntity(s.first) != NULL)
        {
            if (s.second->visible)
            {
                r_renderer::AddToQueue( s.second->texture, 
                                        GetCurrentFrame(s.first), 
                                        s.second->dimensions, 
                                        s.second->fgColor, 
                                        s.second->bgColor, 
                                        { s.second->renderOffsetX, s.second->renderOffsetY },
                                        s.second->angle,
                                        s.second->center,
                                        s.second->flip);
            }
        }
    }
}


