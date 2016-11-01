#ifndef R_FRAMEWORK_BASE
#define R_FRAMEWORK_BASE

#include <SDL2/SDL.h>
#include <vector>
#include "r_framework.h"
#include "r_engine/r_time.h"
#include "r_system/r_window.h"

namespace r_framework
{
  struct R_MOUSESTATE
  {
    int x, y, wheel_x, wheel_y;
    bool LB, MB, RB, X1, X2;
    
    R_MOUSESTATE();
  };
  
  class r_framework_base: public RFramework { 
    
  public:
    SDL_Renderer* Renderer();
    std::pair<int,int> Dimensions();
    
    R_MOUSESTATE MouseState();
    std::pair<int,int> MousePosition();
    const Uint8* Keystates();
    std::string* Input();
    r_time::RTime* Time();
    
    void Init(RGameEngine* game);
    void Pause(){};
    void Resume(){};
    void HandleEvents();
    void Update();
    void Draw();
    void Cleanup();
    r_framework_base();
      
  private:
    RGameEngine* _game;
    WindowSystem _sys_window;
    SDL_Event _event;
    const Uint8* currentKeyStates;
    r_time::RTime _time;
    R_MOUSESTATE _mousestate;
    std::string _input;
    
    EntityID WINDOW;
  };
}
#endif