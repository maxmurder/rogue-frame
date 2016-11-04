/*
* Helper functions & classes for r_component
*/

#ifndef R_COMPONENT_DETAIL_H
#define R_COMPONENT_DETAIL_H    

#include <map>
#include <string>
#include <utility>
#include <iostream>

class Component;

namespace r_component
{
    namespace r_component_detail
    {
        typedef Component *(*CreateComponentFunction)();
        typedef std::map<std::string, CreateComponentFunction> ComponentRegistry;
        // Component registry
        inline ComponentRegistry& GetComponentRegistry()
        {
            static ComponentRegistry reg;
            return reg;
        }
        //Component istantiation helper
        template<class T> Component* CreateComponent() 
        {
            return new T; //actually create the component
        }
        
        //RegistryEntry item struct
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
                    ComponentRegistry& reg = GetComponentRegistry(); //get get the list of registered components
                    CreateComponentFunction func = CreateComponent<T>; //get the accosiated component's creation function
                    
                    std::pair<ComponentRegistry::iterator, bool> ret = 
                        reg.insert(ComponentRegistry::value_type(name, func)); //create a pair of registered components and accociated names
                                                
                    if (ret.second == false) 
                    {   
                        //failure to find component with appropriate name
                        std::cout << "Failed to find registered component with name: " << name << std::endl << "You must register a component with COMPONENT_REGISTER(ComponentName, \"ComponentName\") before using." << std::endl;
                    }
                }
                
                //cleanup
                RegistryEntry(const RegistryEntry<T>&) = delete;
                RegistryEntry& operator=(const RegistryEntry<T>&) = delete;                
        };
    }
}

#endif
