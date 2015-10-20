#ifndef R_ANIMATION_H
#define R_ANIMATION_H
#include <vector>
#include <map>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_util_components.h"

struct AnimationComponent : public Component
{
    std::map<std::string, std::vector<SDL_Rect>> animations;
    
    uint32_t animationSpeed, currentFrame, frameCount;
    std::string currentAnimation;
    
    void SetFrame(uint32_t frame);
    void AddAnimation(std::string name, std::vector<SDL_Rect> frames);
    void SetAnimation(std::string animation);
    SDL_Rect GetCurrentFrame();
    
    AnimationComponent() : animations() { 
    animationSpeed = 0;
    currentFrame = 0;
    frameCount = 0;
    currentAnimation = "NULL";
    };
};

COMPONENT_REGISTER(AnimationComponent, "AnimationComponent");

struct AnimationSystem : public System<AnimationComponent>
{
    void Update();
};
#endif
