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
    int cell_w, cell_h, renderOffsetX, renderOffsetY;
    uint32_t animationSpeed;
    std::string currentAnimation;
    std::map<std::string, std::vector<SDL_Rect>> animations;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( RTexture *textureComponent, int cellWidth, int cellHeight, WHComponent *dimensionsComponent, ColorComponent *foregroundColorComponent, ColorComponent *backgroundColorComponent);
    void AddAnimation(std::string name, std::vector<SDL_Rect> frames);
    void SetAnimation(std::string animation);
    void SetFrame(int frame);
    void Update();
    SDL_Rect GetCurrentFrame();
    
    private:
        uint32_t frameCount, currentFrame;
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");
#endif
