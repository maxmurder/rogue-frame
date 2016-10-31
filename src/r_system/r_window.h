#ifndef R_WINDOW_H
#define R_WINDOW_H
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <SDL2/SDL.h>

#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"

struct WindowComponent : public Component
{
  std::string name;
  uint32_t windowID;
  int height, width;
  bool mouseFocus, keyboardFocus, fullscreen, minimized, shown;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_GLContext context;

  WindowComponent();
};
COMPONENT_REGISTER(WindowComponent, "WindowComponent");

struct WindowSystem : public System<WindowComponent>
{
  void AddComponent(EntityID ownerID, std::string title = "DEFAULT", int width = 640, int height = 480); //adds and itilizes a new window component
  void HandleEvent(SDL_Event &event);  //handles SDL_WINDOWEVENTs
  void Focus(EntityID ownerID); //focuses and raises window to front.
  void Render(EntityID ownerID); // renders the window.
  void FreeWindow(EntityID ownerID); //destroys the window.

  int GetHeight(EntityID ownerID); //returns window height dimension
  int GetWidth(EntityID ownerID); //returns windown width dimension

  bool HasMouseFocus(EntityID ownerID); //returns true if window has mouse focus
  bool HasKeyboardFocus(EntityID ownerID); //returns true if window has keyboard focus
  bool IsMinimized(EntityID ownerID); //returns true if window is minimized
  bool IsShown(EntityID ownerID);  //returns true if window is shown
  
  private:
    void InitWindow(EntityID ownerID, std::string title, int height, int width);
};

#endif
