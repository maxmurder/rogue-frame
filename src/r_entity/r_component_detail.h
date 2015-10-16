#ifndef R_COMPONENT_DETAIL_H
#define R_COMPONENT_DETAIL_H    

#include <map>
#include <string>
#include <utility>

class Component;

namespace r_component
{
    namespace r_component_detail
    {
        typedef Component *(*CreateComponentFunction)(); //pointer to the components create function
        typedef std::map<std::string, CreateComponentFunction> ComponentRegistry; //component registry
    
        inline ComponentRegistry& GetComponentRegistry()
        {
            static ComponentRegistry reg;
            return reg;
        }
        
        template<class T> Component* CreateComponent() 
        {
            return new T;
        }
        
        template<class T> struct RegistryEntry
        {
            public:
                static RegistryEntry<T>& Instance(const std::string& name)
                {
                    static RegistryEntry<T> inst(name);
                    return inst;
                }
            private:
                RegistryEntry(const std::string& name)
                {
                    ComponentRegistry& reg = GetComponentRegistry(); //get get the component registry
                    CreateComponentFunction func = CreateComponent<T>; //get the correct creation function
                    
                    std::pair<ComponentRegistry::iterator, bool> ret = 
                        reg.insert(ComponentRegistry::value_type(name, func)); //get the component type from the registry
                        
                    if (ret.second == false) 
                    {
                        //failure to find component with appropriate name
                    }
                }
                
                //cleanup
                RegistryEntry(const RegistryEntry<T>&) = delete;
                RegistryEntry& operator=(const RegistryEntry<T>&) = delete;                
        };
    }
}

#endif
