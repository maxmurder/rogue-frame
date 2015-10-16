#ifndef R_COMPONENTS_H
#define R_COMPONENTS_H
#include "r_entity/r_component.h"
#include "RSprite.h"

//simple position component
struct XYZComponent : public Component {
        int x, y, z;
};

COMPONENT_REGISTER(XYZComponent, "XYZComponent");

//renderer component (reqires positon and RSprite component)
class RenderComponent : public Component {

        XYZComponent *positionComp;
        RSprite *spriteComp;  
    public:
        void Render(SDL_Renderer *renderer)
        {
            if(GetEntity(owner) != NULL)
            {
                spriteComp->Render(renderer, positionComp->x, positionComp->y);
            }
        }
        void Init(System<XYZComponent> pos, System<RSprite> spr)
        {
            if(GetEntity(owner) != NULL)
            {
                positionComp = pos.components[owner];
                spriteComp = spr.components[owner];
            }
        }
};

COMPONENT_REGISTER(RenderComponent, "RenderComponent");

#endif
