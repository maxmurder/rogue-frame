#ifndef R_SPRITE_H
#define R_SPRITE_H
#include <SDL2/SDL.h>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_animation.h"
#include "r_texture.h"


struct SpriteComponent : public Component
{
    SDL_Texture *texture;
    SDL_Color fgColor;
    SDL_Color bgColor;
    SDL_Rect dimensions;
    
    std::map<std::string, std::vector<SDL_Rect>> animations;
    
    uint32_t animationSpeed, currentFrame, frameCount;
    std::string currentAnimation;
    
    bool visible;
    int renderOffsetX, renderOffsetY;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( SDL_Texture *texture, SDL_Rect dimensions, SDL_Color foregroundColor, SDL_Color backgroundColor);

    SpriteComponent() : animations() { 
    animationSpeed = 0;
    currentFrame = 0;
    frameCount = 0;
    currentAnimation = "NULL";
    renderOffsetX = 0;
    renderOffsetY = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
    visible = false;
    };
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");

struct SpriteSystem: public System<SpriteComponent>
{
    void AddComponent(EntityID ownerID, 
                        SDL_Texture  *texture,
                        SDL_Rect dimensions,
                        SDL_Color fgColor = {0xFF,0xFF,0xFF,0xFF},
                        SDL_Color bgColor = {0x00,0x00,0x00,0x00});
    void SetFrame(EntityID id, uint32_t frame);
    void AddAnimation(EntityID id, std::string name, std::vector<SDL_Rect> frames);
    void SetAnimation(EntityID id, std::string animation);
    SDL_Rect GetCurrentFrame(EntityID id);
    
    void Update();
    void Render();
};

#endif
