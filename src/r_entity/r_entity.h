#ifndef R_ENTITY_H
#define R_ENTITY_H
#include <stdint.h>
#include <map>

struct Entity {
    uint16_t version;
};

typedef uint32_t EntityID; //unique index|version identifier for entities

EntityID CreateEntity(); //creates a new entity and returns its identifier.
void DeleteEntity(EntityID id); //frees the entity and increments the version.
Entity* GetEntity(EntityID id); //returns pointer to the entity or NULL if EntityID does not match a valid index|version.

int NumEntities();
int NumFree();

//class for tracking component systems
template <typename C> struct System {
        std::map<EntityID, C *> components;
};

#endif
