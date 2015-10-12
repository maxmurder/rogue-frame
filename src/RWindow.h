#ifndef RWINDOW_H
#define RWINDOW_H

#include <SDL2/SDL.h>

class RWindow
{
    public:         
        bool Init(std::string title = "Default" , int width = 640, int height = 480);    
        
        void HandleEvent(SDL_Event &event);
        void Focus();
        void Render();
        void Free();
        
        int GetWidth();
        int GetHeight();
        
        bool HasMouseFocus();
        bool HasKeyboardFocus();
        bool IsMinimized();
        bool IsShown();
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        RWindow();

    private:
        std::string _name;
        uint32_t _windowID;
        int _height, _width;
        bool _mouseFocus, _keyboardFocus, _fullScreen, _minimized, _shown;
};
#endif
