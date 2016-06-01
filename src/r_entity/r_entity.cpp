#include "r_entity.h"
#include <vector>

std::vector<Entity> pool; //pool of entities
std::vector<uint16_t> freelist; //list of free indexes

EntityID CreateEntity()
{
    uint16_t index;
    if (freelist.empty())
    {
        pool.push_back(Entity()); //add entity to pool
        freelist.push_back(pool.size() - 1);//add index entry to freelist
    }
    index = freelist.back(); //get a free index 
    freelist.pop_back();
    return (pool[index].version << 16) | index; //return the unique index|version ID
}

void DeleteEntity(EntityID id)
{
    uint16_t index = id & 0xFFFF; //convert ID to index
    ++pool[index].version; //increment index's version
    freelist.push_back(index); //add index to the freelist
}

Entity* GetEntity(EntityID id)
{
    uint16_t index = id & 0xFFFF; //convert EntityID to index
    uint16_t version = id >> 16; //get version of current id
    if(index < pool.size() && pool[index].version == version) //check if index is valid and version is correct
    {
        return &pool[index]; //return the Entity    
    }else
    {
        return NULL; //return NULL if index or version are invalid
    }
}

int NumEntities()
{
    return pool.size();
}

int NumFree()
{
    return freelist.size();
}


