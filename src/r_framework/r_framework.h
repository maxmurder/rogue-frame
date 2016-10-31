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
<<<<<<< HEAD
<<<<<<< HEAD
      virtual void Draw() = 0;
      
      virtual void Cleanup()
=======
      virtual void Draw(RGameEngine* game) = 0;
=======
      virtual void Draw() = 0;
>>>>>>> 349eb67... got text input working
      
<<<<<<< HEAD
<<<<<<< HEAD
      virtual void Cleanup(RGameEngine* game)
>>>>>>> c117f90... added framework for handling windows and input
=======
      void Cleanup()
>>>>>>> ba695ba... added mouse handling to the window framework
=======
      virtual void Cleanup()
>>>>>>> 3d49bb7... sdl now frees resorces
      {
	for(auto s : systems)
	{
	  s->Cleanup();
	}
	systems.clear();
<<<<<<< HEAD
<<<<<<< HEAD
      };
    protected:
      RFramework(){};
      std::vector<ISystem*> systems;
      ~RFramework(){ Cleanup(); };
=======
      }
    
    protected:
      RFramework(){};
      std::vector<ISystem*> systems;
>>>>>>> c117f90... added framework for handling windows and input
=======
      };
    protected:
      RFramework(){};
      std::vector<ISystem*> systems;
      ~RFramework(){ Cleanup(); };
>>>>>>> ba695ba... added mouse handling to the window framework
  };
}
#endif