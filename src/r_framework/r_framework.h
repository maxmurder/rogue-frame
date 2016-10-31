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
      virtual void Pause(RGameEngine* game) = 0;
      virtual void Resume(RGameEngine* game) = 0;
      virtual void HandleEvents(RGameEngine* game) = 0;
      virtual void Update(RGameEngine* game) = 0;
      virtual void Draw(RGameEngine* game) = 0;
      
      void Cleanup()
      {
	for(auto s : systems)
	{
	  s->Cleanup();
	}
	systems.clear();
      };
    protected:
      RFramework(){};
      std::vector<ISystem*> systems;
      ~RFramework(){ Cleanup(); };
  };
}
#endif