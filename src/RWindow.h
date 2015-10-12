#ifndef RWINDOW_H
#define RWINDOW_H

#include <SDL2/SDL.h>

class RWindow
{
    public:         
        bool Init(std::string title = "Default" , int width = 640, int height = 480);
        
        SDL_Renderer* CreateRenderer();
        
        void HandleEvent(SDL_Event &event);
        
        void Free();
        
        int GetWidth();
        int GetHeight();
        
        bool HasMouseFocus();
        bool HasKeyboardFocus();
        bool IsMinimized();
        RWindow();

    private:
        SDL_Window* _window;
        std::string _name;
        int _height, _width;
        bool _mouseFocus, _keyboardFocus, _fullScreen, _minimized;
};
#endif
