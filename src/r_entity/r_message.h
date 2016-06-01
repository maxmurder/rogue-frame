#ifndef R_MESSAGE_H
#define R_MESSAGE_H

#include <string>

typedef uint32_t EntityID;

struct Message
{
    EntityID id;
    std::string message;
};


#endif
