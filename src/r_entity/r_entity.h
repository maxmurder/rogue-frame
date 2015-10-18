#ifndef R_ENTITY_H
#define R_ENTITY_H
#include <stdint.h>
#include <map>

/*
    r_entity contains functionality for handeling entities.
    CreateEntity() retrns a unique identifier for an entitity, which is a comination of a map index and version. 
    DeleteEntity(EntityID) frees the entity index and increment the version, this will result in subsiquent calls to GetEntity(EntityID) with out-of-date id's to return NULL.
    GetEntity(EntityID) returns a pointer to the entity if the supplied EntityID is valid. 
*/
struct Component;

struct Entity {
    uint16_t version;
};

typedef uint32_t EntityID; //unique index|version identifier for entities

EntityID CreateEntity(); //creates a new entity and returns its identifier.
void DeleteEntity(EntityID id); //frees the entity and increments the version.
Entity* GetEntity(EntityID id); //returns pointer to the entity or NULL if EntityID does not match a valid index|version.

int NumEntities(); //retrns number of entities in the pool.
int NumFree(); //returns number of free entities in the pool. 

//class for tracking system components
template <typename C> struct System {
        std::map<EntityID, C *> components;
        
        virtual void AddComponent(Component *component, EntityID ownerID)
        {
            components[ownerID] = dynamic_cast<C *>(component);
        }
};

#endif
