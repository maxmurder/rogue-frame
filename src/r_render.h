#ifndef R_RENDER_H
#define R_RENDER_H
#include "r_entity/r_component.h"
#include "r_util_components.h"
#include "r_sprite.h"

//renderer component (reqires positon and RSprite component)
struct RenderComponent : public Component 
{
        XYZComponent *positionComp;
        SpriteComponent *spriteComp;  
        bool render;
    public:
        void Init(System<XYZComponent> pos, System<SpriteComponent> spr, bool rend = false)
        {
            if(GetEntity(ownerID) != NULL)
            {
                positionComp = pos.components[ownerID];
                spriteComp = spr.components[ownerID];
                render = rend;
            }
        }
};

COMPONENT_REGISTER(RenderComponent, "RenderComponent");

struct RenderSystem: public System<RenderComponent>
{
    void AddComponent(Component *component, EntityID ownerID, System<XYZComponent> pos, System<SpriteComponent> spr, bool render = false);
    void RemoveComponent(EntityID ownerID);
    void Render(SDL_Renderer *renderer);
};

#endif
