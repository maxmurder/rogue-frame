#include "r_framework_main.h"
#include "r_utils/r_renderer.h"

namespace r_framework {
  
  std::pair< int, int > r_framework_main::MousePosition()
  {
    return std::make_pair(_mouse_x,_mouse_y);
  }

  const Uint8* r_framework_main::Keystates()
  {
    return currentKeyStates;
  }
  
  SDL_Renderer* r_framework_main::Renderer()
  {
    return _sys_window.components[MAIN_WINDOW]->renderer;
  }
  
  std::pair<int, int> r_framework_main::Dimensions()
  {
    return std::make_pair(_sys_window.GetWidth(MAIN_WINDOW), _sys_window.GetHeight(MAIN_WINDOW) );
  }

  void r_framework_main::Init(RGameEngine* game)
  {
    _sys_window.AddComponent(MAIN_WINDOW);
    currentKeyStates = SDL_GetKeyboardState(NULL);
    SDL_StartTextInput();
  }
  
  void r_framework_main::HandleEvents(RGameEngine* game)
  {
    while ( SDL_PollEvent( &_event ) )
    {
      if( _event.type == SDL_QUIT )
      {
	game->Quit();
      }else if ( _event.type == SDL_MOUSEMOTION || _event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP )
      {
	SDL_GetMouseState(&_mouse_x, &_mouse_y);
      }
      
      if ( currentKeyStates[SDL_SCANCODE_ESCAPE] )
      {
	game->Quit();
      }
      //get keyboard text input
      _input = r_SDL::TextInputHandler(_event, _input);
      
      _sys_window.HandleEvent(_event);
    }
  }
  
  void r_framework_main::Draw(RGameEngine* game)
  {
    r_renderer::Render(_sys_window.components[MAIN_WINDOW]->renderer);
  }

  r_framework_main::r_framework_main()
  {
    systems.push_back(&_sys_window);
  }
}