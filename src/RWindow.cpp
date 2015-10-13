#include <iostream>
#include <sstream>
#include "RWindow.h"

using namespace std;

bool RWindow::Init(std::string title, int width, int height)
{    
    //create window
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( window != NULL)
    {
        _name = title;
        _mouseFocus = true;
        _keyboardFocus = true;
        _width = width;
        _height = height;
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if (renderer == NULL)
        {
           cout << "Unable to create renderer :: " << SDL_GetError() << endl;
           SDL_DestroyWindow(window);
           window = NULL;
        }else
        {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            _windowID = SDL_GetWindowID(window);
            _shown = true;
        }
    }else
    {
        cout << "Unable to create window :: " << SDL_GetError() << endl;
    }
    return window != NULL && renderer != NULL;
}

void RWindow::HandleEvent( SDL_Event& event )
{
    if ( event.type == SDL_WINDOWEVENT && event.window.windowID == _windowID)
    {
        bool updateCaption = false;
        
        switch ( event.window.event )
        {
        case SDL_WINDOWEVENT_SHOWN:
            _shown = true;
            break;
            
        case SDL_WINDOWEVENT_HIDDEN:
            _shown = false;
            break;
            
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            _width = event.window.data1;
            _height = event.window.data2;
            SDL_RenderPresent( renderer );
            break;
            
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( renderer );
            break;
            
        case SDL_WINDOWEVENT_ENTER:
            _mouseFocus = true;
            updateCaption = true;
            break;
            
        case SDL_WINDOWEVENT_LEAVE:
            _mouseFocus = false;
            updateCaption = true;
            break;
            
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            _mouseFocus = true;
            _keyboardFocus = true;
            updateCaption = true;
            break;
            
        case SDL_WINDOWEVENT_FOCUS_LOST:
            _mouseFocus = false;
            _keyboardFocus = false;
            updateCaption = true;
            break;
            
        case SDL_WINDOWEVENT_MINIMIZED:
            _minimized = true;
            break;
            
        case SDL_WINDOWEVENT_MAXIMIZED:
            _minimized = false;
            break;
            
        case SDL_WINDOWEVENT_RESTORED:
            _minimized = false;
            break;
            
        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow(window);
            break;
        }
        
        if (updateCaption)
        {
            stringstream caption;
            caption << _name << " - ID: " << " MouseFocus: " << ( ( _mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus: " <<  ( ( _keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( window, caption.str().c_str() );
        }
        
     //escape fullscreen mode
    }else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
    {
        if ( _fullScreen )
        {
            SDL_SetWindowFullscreen(window, SDL_FALSE);
            _fullScreen = false;
        }
    }
}

void RWindow::Focus()
{
    if(!_shown)
    {
        SDL_ShowWindow(window);
    }
    //bring window forward
    SDL_RaiseWindow(window);
}

void RWindow::Render()
{
    if ( !_minimized )
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );
        
        SDL_RenderPresent( renderer );
    }
}

int RWindow::GetWidth()
{
    return _width;
}

int RWindow::GetHeight()
{
    return _height;
}

bool RWindow::HasMouseFocus()
{
    return _mouseFocus;
}

bool RWindow::HasKeyboardFocus()
{
    return _keyboardFocus;
}

bool RWindow::IsMinimized()
{
    return _minimized;
}

bool RWindow::IsShown()
{
    return _shown;
}

void RWindow::Free()
{   
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    _mouseFocus = false;
    _keyboardFocus = false;
    _height = 0;
    _width = 0;
}

RWindow::RWindow()
{
    window = NULL;
    _mouseFocus = false;
    _keyboardFocus = false;
    _fullScreen = false;
    _minimized = false;
    _height = 0;
    _width = 0;
}


