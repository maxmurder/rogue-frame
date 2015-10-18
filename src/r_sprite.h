#ifndef R_SPRITE_H
#define R_SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_util_components.h"

struct SpriteComponent : public Component
{
    RTexture *texture;
    ColorComponent *fgColor;
    ColorComponent *bgColor;
    WHComponent *dimensions;
    WHComponent *cellDimensions;
    int renderOffsetX, renderOffsetY;
    uint32_t animationSpeed;
    std::string currentAnimation;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( RTexture *textureComponent,  WHComponent *cellDimensionsComponent, WHComponent *dimensionsComponent, ColorComponent *foregroundColorComponent, ColorComponent *backgroundColorComponent);
    void AddAnimation(std::string name, std::vector<SDL_Rect> frames);
    void SetAnimation(std::string animation);
    void SetFrame(int frame);
    void Update();
    SDL_Rect GetCurrentFrame();
    
    SpriteComponent();
    
    private:
        uint32_t currentFrame, frameCount;
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");
#endif
