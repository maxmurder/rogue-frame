#ifndef RWINDOW_H
#define RWINDOW_H

#include <SDL2/SDL.h>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"

struct WindowComponent : public Component
{
  std::string name;
  uint32_t windowID;
  int height, width;
  bool mouseFocus, keyboadFocus, fullscreen, minimized, shown;
};

class RWindow
{
    public:
        bool Init(std::string title = "Default" , int width = 640, int height = 480);

        void HandleEvent(SDL_Event &event);
        void Focus();
        void Render();
        void FreeWindow();

        int GetWidth();
        int GetHeight();

        bool HasMouseFocus();
        bool HasKeyboardFocus();
        bool IsMinimized();
        bool IsShown();

        SDL_Window* window;
        SDL_Renderer* renderer;

        RWindow();
        ~RWindow();

    private:
        std::string _name;
        uint32_t _windowID;
        int _height, _width;
        bool _mouseFocus, _keyboardFocus, _fullScreen, _minimized, _shown;
};
#endif
