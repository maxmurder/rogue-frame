#include "r_util_components.h"

int UnicodeSymbolComponent::GetIndex(uint16_t symbol)
{
    for(uint32_t i = 0; i < symbols.size(); i++)
    {
        if (symbols[i] == symbol)
        {
            return i;
        }
    }
    return -1;
}

void ColorComponent::SetColor(SDL_Color c)
{
    color.r = c.r;
    color.g = c.g;
    color.b = c.b;
    color.a = c.a;
}
