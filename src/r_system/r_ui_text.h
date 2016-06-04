#ifndef R_UI_TEXT_H
#define R_UI_TEXT_H
#include <SDL2/SDL.h>
#include "r_utils/r_renderer.h"
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include <map>

struct UITextComponent : public Component
{
    SDL_Texture *texture;
    std::wstring text;
    SDL_Rect displayRect;

    SDL_Color foregroundColor;
    SDL_Color backgroundColor;
    std::map<wchar_t, SDL_Rect> symbols;
};

COMPONENT_REGISTER(UITextComponent, "UITextComponent");

struct UITextSystem : public System<UITextComponent>
{
    void AddComponent(EntityID ownerID,
                        SDL_Texture *texture,
                        std::map<wchar_t, SDL_Rect> symbols,
                        SDL_Rect displayRect,
                        std::wstring text = L"",
                        SDL_Color fgColor = {0xFF,0xFF,0xFF,0xFF},
                        SDL_Color bgColor = {0x00, 0x00, 0x00, 0x00});
    void SetText(EntityID ownerID, std::wstring text);
    void SetDisplayRect(EntityID ownerID, SDL_Rect displayRect);
    void Render();
};

#endif
