#ifndef R_COMPONENT_H
#define R_COMPONENT_H

#include <string>
#include "r_entity.h"
#include "r_component_detail.h"

/*
r_component contains base class and functionality for creating and destroying user-defined components.
User must register a component by using the macro:
COMPONENT_REGISTER(ComonentName, "ComponentName");
following a class derived from struct Component.
You may then instatiate the component using r_component::Create("ComponentName", OwnerID);
Destroy the component using std::Destroy(Component *) to cleanup.
*/

//base class for components
struct Component {
        EntityID ownerID;
        Component(){};
        virtual ~Component(){};
};

namespace r_component
{
    Component* Create(const std::string& name, EntityID ownerID); //create component function
    void Destroy(const Component* comp); //destroy component function
}

/* 
* Component registry macro
* When defining a new component type use this macro to register it.
* Usage:
*   struct SomeComponent : public Component {}; // define the component struct.
*   COMPONENT_REGISTER(SomeComponent, "SomeComponent"); // register the component for use by systems.
*/
#define COMPONENT_REGISTER(TYPE, NAME)                                                                                  \
    namespace r_component {                                                                                             \
    namespace r_component_detail {                                                                                      \
    namespace                                                                                                           \
    {                                                                                                                   \
        template<class T> class ComponentRegistration;                                                                  \
                                                                                                                        \
        template<> class ComponentRegistration<TYPE>                                                                    \
        {                                                                                                               \
            static const ::r_component::r_component_detail::RegistryEntry<TYPE>& reg;                                   \
        };                                                                                                              \
                                                                                                                        \
        const ::r_component::r_component_detail::RegistryEntry<TYPE>&                                                   \
            ComponentRegistration<TYPE>::reg = ::r_component::r_component_detail::RegistryEntry<TYPE>::Instance(NAME);  \
        }                                                                                                               \
    }                                                                                                                   \
}                                                                                                                       \

#endif
