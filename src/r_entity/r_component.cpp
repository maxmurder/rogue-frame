#include "r_component.h"

#include <string>

#include "r_component_detail.h"

Component* r_component::Create(const std::string& name)
{
    r_component_detail::ComponentRegistry& reg = r_component_detail::GetComponentRegistry(); //get the component registry
    r_component_detail::ComponentRegistry::iterator it = reg.find(name); //find the component in the registry
    
    if (it == reg.end())
    {
        return nullptr; //no component registered to the supplied name
    }
    
    r_component_detail::CreateComponentFunction func = it->second; //get the component's pointer
    return func(); //return the pointer
}

void r_component::Destroy(const Component* comp)
{
    delete comp;
}
