#ifndef R_COMPONENT_H
#define R_COMPONENT_H

#include <string>
#include "r_entity.h"
#include "r_component_detail.h"


//base class for components
struct Component {
        EntityID owner;
        Component(){};
        virtual ~Component(){};
};

namespace r_component
{
    Component* Create(const std::string& name); //create component function
    void Destroy(const Component* comp); //destroy component function
}

//component type registry macro
#define COMPONENT_REGISTER(TYPE, NAME)                                                                      \
    namespace r_component {                                                                                 \
    namespace r_component_detail {                                                                          \
    namespace                                                                                               \
    {                                                                                                       \
        template<class T> class ComponentRegistration;                                                      \
                                                                                                            \
        template<> class ComponentRegistration<TYPE>                                                        \
        {                                                                                                   \
            static const ::r_component::r_component_detail::RegistryEntry<TYPE>& reg;                       \
        };                                                                                                  \
                                                                                                            \
        const ::r_component::r_component_detail::RegistryEntry<TYPE>&                                       \
            ComponentRegistration<TYPE>::reg = ::r_component::r_component_detail::RegistryEntry<TYPE>::Instance(NAME);  \
        }                                                                                                   \
    }                                                                                                       \
}                                                                                                           \

#endif
