#ifndef R_COMPONENTS_H
#define R_COMPONENTS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "r_entity/r_component.h"

//simple position component
struct XYZComponent : public Component {
        double x, y, z;
};

COMPONENT_REGISTER(XYZComponent, "XYZComponent");

struct WHComponent : public Component {
    uint16_t w, h;
};

COMPONENT_REGISTER(WHComponent, "WHComponent");

struct StringComponent : public Component
{
    std::wstring text;
};
COMPONENT_REGISTER(StringComponent, "StringComponent");

struct UnicodeSymbolComponent : public Component
{
    std::vector<uint16_t> symbols;
    int GetIndex(uint16_t symbol);
};

COMPONENT_REGISTER(UnicodeSymbolComponent, "UnicodeSymbolComponent");

struct FontComponent : public Component
{
    TTF_Font *font;
    uint32_t pntsize;
};

COMPONENT_REGISTER(FontComponent, "FontComponent");

struct ColorComponent : public Component
{
    SDL_Color color;
    void SetColor(SDL_Color color);
};

COMPONENT_REGISTER(ColorComponent, "ColorComponent");

#endif
