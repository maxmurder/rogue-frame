#include "r_ui_text.h"

void UITextSystem::AddComponent(EntityID ownerID, SDL_Texture *texture, std::map<wchar_t, SDL_Rect> symbols, SDL_Rect displayRect, std::wstring text, SDL_Color fgColor, SDL_Color bgColor)
{
    System::AddComponent(r_component::Create("UITextComponent", ownerID), ownerID);
    components[ownerID]->texture = texture;
    components[ownerID]->displayRect = displayRect;
    components[ownerID]->text = text;
    components[ownerID]->foregroundColor = fgColor;
    components[ownerID]->backgroundColor = bgColor;
    components[ownerID]->text = text;
    components[ownerID]->symbols = symbols;
}

void UITextSystem::SetText(EntityID ownerID, std::wstring text)
{
    if(GetComponent(ownerID) != NULL)
    {
        components[ownerID]->text = text;
    }
}

void UITextSystem::SetDisplayRect(EntityID ownerID, SDL_Rect displayRect)
{
    if(GetComponent(ownerID) != NULL)
    {
        components[ownerID]->displayRect = displayRect;
    }
}

void UITextSystem::Render()
{
    for (auto &e : components)
    {
        if(GetEntity(e.first) != NULL)
        {
            int i = 0, r = 0;
            for(auto &c : e.second->text)
            {
                if((c == 0x000A) || (c == 0x000D))
                {
                    r++;
                    i = 0;
                }else
                {
                    r_renderer::AddToQueue(e.second->texture, 
                                            e.second->symbols[c], 
                                            {
                                                e.second->displayRect.x + (i % (e.second->displayRect.w / e.second->symbols[c].w) * e.second->symbols[c].w), 
                                                e.second->displayRect.y + ( r * e.second->symbols[c].h),
                                                e.second->symbols[c].w,
                                                e.second->symbols[c].h
                                            },
                                            e.second->foregroundColor,
                                            e.second->backgroundColor);
                    i++;       
                    if(i % (e.second->displayRect.w / e.second->symbols[c].w) == 0)
                    {
                        r++;
                    }
                }
            }
        }
    }
}
