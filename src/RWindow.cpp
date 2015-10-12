#include <iostream>
#include <sstream>
#include "RWindow.h"

using namespace std;

bool RWindow::Init(std::string title, int width, int height)
{
    _name = title;
    _window = SDL_CreateWindow( _name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( _window != NULL)
    {
        _mouseFocus = true;
        _keyboardFocus = true;
        _width = width;
        _height = height;
        return true;
    }else
    {
        cout << "Unable to create window :: " << SDL_GetError() << endl;
    }
    return false;
}

SDL_Renderer* RWindow::CreateRenderer()
{
    return SDL_CreateRenderer( _window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void RWindow::HandleEvent( SDL_Event& event )
{
    if ( event.type == SDL_WINDOWEVENT)
    {
        bool updateCaption = false;
        
        switch ( event.window.event )
        {
    
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            _width = event.window.data1;
            _height = event.window.data2;
            break;
        case SDL_WINDOWEVENT_EXPOSED:
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
            updateCaption = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            _mouseFocus = false;
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
        }
        
        if (updateCaption)
        {
            stringstream caption;
            caption << _name << " - MouseFocus: " << ( ( _mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus: " <<  ( ( _keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( _window, caption.str().c_str() );
        }
        
     //escape fullscreen mode
    }else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
    {
        if ( _fullScreen )
        {
            SDL_SetWindowFullscreen(_window, SDL_FALSE);
            _fullScreen = false;
        }
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

void RWindow::Free()
{
    SDL_DestroyWindow(_window);
    _mouseFocus = false;
    _keyboardFocus = false;
    _fullScreen = false;
    _minimized = false;
    _height = 0;
    _width = 0;
}

RWindow::RWindow()
{
    _window = NULL;
    _mouseFocus = false;
     _keyboardFocus = false;
    _fullScreen = false;
    _minimized = false;
    _height = 0;
    _width = 0;
}


