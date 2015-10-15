#ifndef R_ENTITY_H
#define R_ENTITY_H
#include <stdint.h>
#include <map>

struct Entity {};

typedef uint32_t EntityID; //unique index|version identifier for entities

EntityID CreateEntity(); //creates a new entity and returns its identifier.
void DeleteEntity(EntityID id); //frees the entity and increments the version.
Entity* GetEntity(EntityID id); //returns pointer to the entity or NULL if EntityID does not match a valid index|version.

//base class for components
struct Component {
        Component(EntityID id) : owner(id){}
        EntityID owner;
};

//class for tracking component systems
template <typename C> class System {
    public:
        std::map<EntityID, C *> components;
};

#endif
