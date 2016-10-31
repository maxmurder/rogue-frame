#include "r_framework_base.h"
#include "r_utils/r_renderer.h"

namespace r_framework {
  
  std::pair< int, int > r_framework_base::MousePosition()
  {
    return std::make_pair(_mousestate.x,_mousestate.y);
  }
  
  R_MOUSESTATE r_framework_base::MouseState()
  {
    return _mousestate;
  }


  const Uint8* r_framework_base::Keystates()
  {
    return currentKeyStates;
  }
  
  std::string* r_framework_base::Input()
  {
    return &_input;
  }

  
  SDL_Renderer* r_framework_base::Renderer()
  {
    return _sys_window.components[WINDOW]->renderer;
  }
  
  std::pair<int, int> r_framework_base::Dimensions()
  {
    return std::make_pair(_sys_window.GetWidth(WINDOW), _sys_window.GetHeight(WINDOW) );
  }
  
  r_time::RTime* r_framework_base::Time()
  {
    return &_time;
  }

  void r_framework_base::Init(RGameEngine* game)
  {
    WINDOW = CreateEntity();
    _sys_window.AddComponent(WINDOW);
    currentKeyStates = SDL_GetKeyboardState(NULL);
    SDL_StartTextInput();
  }
  
  void r_framework_base::Update(RGameEngine* game)
  {
    _time.Update();
  }
  
  void r_framework_base::HandleEvents(RGameEngine* game)
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
  
  void r_framework_base::Draw()
  {
    r_renderer::Render(_sys_window.components[WINDOW]->renderer);
  }
  
  void r_framework_base::Cleanup()
  {
  	_sys_window.FreeWindow(WINDOW);
    SDL_StopTextInput();
    r_framework::RFramework::Cleanup();
  }


  r_framework_base::r_framework_base()
  {
    systems.push_back(&_sys_window);
  }
  
  R_MOUSESTATE::R_MOUSESTATE()
  {
    x = 0;
    y = 0; 
    wheel_x = 0;
    wheel_y = 0;
    LB = false;
    MB = false;
    RB = false;
    X1 = false;
    X2 = false;
  }
}