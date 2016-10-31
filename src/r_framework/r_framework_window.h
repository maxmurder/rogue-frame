#ifndef R_FRAMEWORK_WINDOW
#define R_FRAMEWORK_WINDOW

#include<SDL2/SDL.h>
#include "r_framework.h"
#include "r_engine/r_time.h"
#include "r_system/r_window.h"

namespace r_framework
{
  struct R_MOUSESTATE
  {
    int x, y, wheel_x, wheel_y;
    bool LB, MB, RB, X1, X2;
  };
  
  class r_framework_window: public RFramework { 
    
  public:
    SDL_Renderer* Renderer();
    std::pair<int,int> Dimensions();
    R_MOUSESTATE MouseState();
    std::pair<int,int> MousePosition();
    const Uint8* Keystates();

    
    void Init(RGameEngine* game);
    void Pause(RGameEngine* game){};
    void Resume(RGameEngine* game){};
    void HandleEvents(RGameEngine* game);
    void Update(RGameEngine* game){};
    void Draw(RGameEngine* game);
    r_framework_window();
      
  private:
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