#ifndef R_COMPONENTS_H
#define R_COMPONENTS_H
#include "r_entity.h"
#include "RSprite.h"

//simple position component
class PositionComponent : public Component {
    public:
        int x, y, z;   
        PositionComponent(EntityID id) : Component(id) {};
};

//renderer component (reqires positon and RSprite component)
class RenderComponent : public Component {
    public:
        PositionComponent *positionComp;
        RSprite *spriteComp;  
        void Render(SDL_Renderer *renderer)
        {
            spriteComp->Render(renderer, positionComp->x, positionComp->y);
        }
        RenderComponent(EntityID id, System<PositionComponent> & pos, System<RSprite> & spr) 
            : Component(id), positionComp(pos.components[owner]), spriteComp(spr.components[owner]) {}
};

#endif
