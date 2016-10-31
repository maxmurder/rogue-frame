#include "r_framework_window.h"
#include "r_utils/r_renderer.h"

namespace r_framework {
  
  std::pair< int, int > r_framework_window::MousePosition()
  {
    return std::make_pair(_mousestate.x,_mousestate.y);
  }
  
  R_MOUSESTATE r_framework_window::MouseState()
  {
    return _mousestate;
  }


  const Uint8* r_framework_window::Keystates()
  {
    return currentKeyStates;
  }
  
  SDL_Renderer* r_framework_window::Renderer()
  {
    return _sys_window.components[WINDOW]->renderer;
  }
  
  std::pair<int, int> r_framework_window::Dimensions()
  {
    return std::make_pair(_sys_window.GetWidth(WINDOW), _sys_window.GetHeight(WINDOW) );
  }

  void r_framework_window::Init(RGameEngine* game)
  {
    WINDOW = CreateEntity();
    _sys_window.AddComponent(WINDOW);
    currentKeyStates = SDL_GetKeyboardState(NULL);
    SDL_StartTextInput();
  }
  
  void r_framework_window::HandleEvents(RGameEngine* game)
  {
    while ( SDL_PollEvent( &_event ) )
    {
      if( _event.type == SDL_QUIT )
      {
	game->Quit();
      }else if ( _event.type == SDL_MOUSEMOTION )
      {
	SDL_GetMouseState(&_mousestate.x, &_mousestate.y);
      }else if ( _event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP )
      {
	switch ( _event.button.button ) {
	  case SDL_BUTTON_LEFT:
	     _mousestate.LB = ( _event.type != SDL_MOUSEBUTTONUP );
	     break;
	  case SDL_BUTTON_RIGHT:
	    _mousestate.RB = ( _event.type != SDL_MOUSEBUTTONUP );
	    break;
	  case SDL_BUTTON_MIDDLE:
	    _mousestate.MB = ( _event.type != SDL_MOUSEBUTTONUP );
	    break;
	  case SDL_BUTTON_X1:
	    _mousestate.X1 = ( _event.type != SDL_MOUSEBUTTONUP );
	    break;
	  case SDL_BUTTON_X2:
	    _mousestate.X2 = ( _event.type != SDL_MOUSEBUTTONUP );
	    break;
	}
      }else if (_event.type == SDL_MOUSEWHEEL)
      {
	_mousestate.wheel_x += _event.wheel.x;
	_mousestate.wheel_y += _event.wheel.y;
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
  
  void r_framework_window::Draw(RGameEngine* game)
  {
    r_renderer::Render(_sys_window.components[WINDOW]->renderer);
  }

  r_framework_window::r_framework_window()
  {
    systems.push_back(&_sys_window);
  }
}