#ifndef R_ANIMATION_H
#define R_ANIMATION_H
#include <vector>
#include <map>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_utils/r_util_components.h"

struct AnimationComponent : public Component
{
    std::map<std::string, std::vector<SDL_Rect>> animations;

    uint32_t animationSpeed, currentFrame, frameCount;
    std::string currentAnimation;

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
    void SetFrame(EntityID id, uint32_t frame);
    void AddAnimation(EntityID id, std::string name, std::vector<SDL_Rect> frames);
    void SetAnimation(EntityID id, std::string animation);
    SDL_Rect GetCurrentFrame(EntityID id);
};
#endif
