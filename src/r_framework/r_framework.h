#ifndef R_FRAMEWORK_H
#define R_FRAMEWORK_H

#include <vector>
#include "r_engine/r_engine.h"
#include "r_entity/r_entity.h"
#include "r_utils/r_SDL.h"

/*
* Abstract Framework class to act as an interface for system frameworks
* Automatically cleans up any ISystem objects present in the systems list.
* Provides a way to organize groups of systems and related functionality.
*/

namespace r_framework 
{
  class RFramework
  {
    public:
      virtual void Init(RGameEngine* game) = 0; //framework initilization method
      virtual void Pause() = 0; // framework pause method to be called during RGameState Pause() step.
      virtual void Resume() = 0; // framework resume method to be called during RGameState Resume() step.
      virtual void HandleEvents() = 0; // framework HandleEvents method to be called every tick during RGameState HandleEvents method.
      virtual void Update() = 0; // framework Update method to be called every tick from RGameState Update step.
      virtual void Draw() = 0; // framework draw method to be called every frame from RGameState Draw step.
      //method to clean up member systems
      virtual void Cleanup() 
      {
            for(auto s : systems)
            {
              s->Cleanup();
            }
            systems.clear();
      };
    protected:
      RFramework(){};
      ~RFramework(){ Cleanup(); };
      std::vector<ISystem*> systems;
      void AddSystem(ISystem* system) {systems.push_back(system);} //adds an ISystem to the member system list.
  };
}
#endif