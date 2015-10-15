#ifndef R_COMPONENTS_H
#define R_COMPONENTS_H
#include "r_entity.h"
#include "RSprite.h"

//simple position component
struct XYZComponent : public Component {
        int x, y, z;   
        XYZComponent(EntityID id) : Component(id) {};
};

//renderer component (reqires positon and RSprite component)
class RenderComponent : public Component {

        XYZComponent *positionComp;
        RSprite *spriteComp;  
    public:
        void Render(SDL_Renderer *renderer)
        {
            spriteComp->Render(renderer, positionComp->x, positionComp->y);
        }
        RenderComponent(EntityID id, System<XYZComponent> & pos, System<RSprite> & spr) 
            : Component(id), positionComp(pos.components[owner]), spriteComp(spr.components[owner]) {}
};
/*
class TestParticle : public Component {

        RenderComponent *renderComp;
        XYZComponent *positionComp;
        XYZComponent *velocityComp;
        RTimer *timerComp;
        RSprite *spriteComp;
     public:       
        TestParticle(EntityID id, System<XYZComponent> & pos, System<XYZComponent> & vel, System<RSprite> & spr, System<RenderComponent> & ren, System<RTimer> & tim)
            : Component(id), positionComp(pos.components[owner]), velocityComp(vel.components[owner]), spriteComp(spr.components[owner]),renderComp(ren.components[owner]), timerComp(tim.components[owner]){}
};

class TestParticleEmmiter : public Component {


};
*/
#endif
