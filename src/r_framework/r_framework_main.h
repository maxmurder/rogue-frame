#ifndef R_FRAMEWORK_MAIN
#define R_FRAMEWORK_MAIN

#include<SDL2/SDL.h>
#include "r_framework.h"
#include "r_engine/r_time.h"
#include "r_system/r_window.h"

namespace r_framework
{
  struct MouseState
  {
    int x, y;
    bool LB, MB, RB;
  };
  
  class r_framework_main: public RFramework { 
    
  public:
    SDL_Renderer* Renderer();
    std::pair<int, int> Dimensions();
    std::pair<int,int> MousePosition();
    const Uint8* Keystates();

    
    void Init(RGameEngine* game);
    void Pause(RGameEngine* game){};
    void Resume(RGameEngine* game){};
    void HandleEvents(RGameEngine* game);
    void Update(RGameEngine* game){};
    void Draw(RGameEngine* game);
    r_framework_main();
      
  private:
    WindowSystem _sys_window;
    SDL_Event _event;
    const Uint8* currentKeyStates;
    r_time::RTime _time;
    int _mouse_x, _mouse_y;
    std::string _input;
    
    EntityID MAIN_WINDOW;
  };
}
#endif