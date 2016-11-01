#ifndef R_FRAMEWORK_H
#define R_FRAMEWORK_H

#include <vector>
#include "r_engine/r_engine.h"
#include "r_entity/r_entity.h"
#include "r_utils/r_SDL.h"

namespace r_framework 
{
  class RFramework
  {
    public:
      virtual void Init(RGameEngine* game) = 0;
      virtual void Pause() = 0;
      virtual void Resume() = 0;
      virtual void HandleEvents() = 0;
      virtual void Update() = 0;
      virtual void Draw() = 0;

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
      void AddSystem(ISystem* system) {systems.push_back(system);}
  };
}
#endif