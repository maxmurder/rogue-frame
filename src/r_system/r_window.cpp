#include <iostream>
#include <sstream>
#include "r_window.h"

void WindowSystem::AddComponent(EntityID ownerID, std::string title, int width, int height)
{
  System::AddComponent(r_component::Create("WindowComponent", ownerID), ownerID);
  InitWindow(ownerID, title, width, height);
}

void WindowSystem::InitWindow(EntityID ownerID, std::string title, int width, int height)
{
    
    components[ownerID]->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if( components[ownerID]->window != NULL)
    {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        components[ownerID]->name = title;
        components[ownerID]->mouseFocus = true;
        components[ownerID]->keyboardFocus = true;
        components[ownerID]->width = width;
        components[ownerID]->height = height;
        components[ownerID]->renderer = SDL_CreateRenderer(components[ownerID]->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(components[ownerID]->renderer == NULL)
        {
            std::cout << "Unable to create renderer :: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(components[ownerID]->window);
            components[ownerID]->window = NULL;
        }else
        {
            SDL_SetRenderDrawColor(components[ownerID]->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            components[ownerID]->windowID = SDL_GetWindowID(components[ownerID]->window);
            components[ownerID]->shown = true;
	}
	components[ownerID]->context = SDL_GL_CreateContext(components[ownerID]->window);
	if( components[ownerID]->context == NULL )
	{
	    std::cout  << "Unable to create context :: " << SDL_GetError() << std::endl;
	}
	
    }else
    {
        std::cout << "Unable to create window :: " << SDL_GetError() << std::endl;
    }
}

void WindowSystem::HandleEvent( SDL_Event& event )
{
  for(auto &c : components)
  {
    if(GetEntity(c.first) != NULL)
    {
      if ( event.type == SDL_WINDOWEVENT && event.window.windowID == c.second->windowID)
      {
        bool updateCaption = false;

        switch ( event.window.event )
        {
        case SDL_WINDOWEVENT_SHOWN:
            c.second->shown = true;
            break;

        case SDL_WINDOWEVENT_HIDDEN:
            c.second->shown = false;
            break;

        case SDL_WINDOWEVENT_SIZE_CHANGED:
            c.second->width = event.window.data1;
            c.second->height = event.window.data2;
            SDL_RenderPresent( c.second->renderer );
            break;

        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( c.second->renderer );
            break;

        case SDL_WINDOWEVENT_ENTER:
            c.second->mouseFocus = true;
            updateCaption = true;
            break;

        case SDL_WINDOWEVENT_LEAVE:
            c.second->mouseFocus = false;
            updateCaption = true;
            break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
            c.second->mouseFocus = true;
            c.second->keyboardFocus = true;
            updateCaption = true;
            break;

        case SDL_WINDOWEVENT_FOCUS_LOST:
            c.second->mouseFocus = false;
            c.second->keyboardFocus = false;
            updateCaption = true;
            break;

        case SDL_WINDOWEVENT_MINIMIZED:
            c.second->minimized = true;
            break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            c.second->minimized = false;
            break;

        case SDL_WINDOWEVENT_RESTORED:
            c.second->minimized = false;
            break;

        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow(c.second->window);
            break;
        }
        if (updateCaption)
        {
            std::stringstream caption;
            caption << c.second->name << " - ID: " << c.second->windowID << " MouseFocus: " << ( ( c.second->mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus: " <<  ( ( c.second->keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( c.second->window, caption.str().c_str() );
        }

       //escape fullscreen mode
      }else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
      {
        if ( c.second->fullscreen )
        {
            SDL_SetWindowFullscreen(c.second->window, SDL_FALSE);
            c.second->fullscreen = false;
        }
      }
    }
  }
}

void WindowSystem::Focus(EntityID ownerID)
{
  if(GetEntity(ownerID) != NULL)
  {
    if(components[ownerID]->shown)
    {
      SDL_ShowWindow(components[ownerID]->window);
    }
    SDL_RaiseWindow(components[ownerID]->window);
  }
}

void WindowSystem::Render(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
        if ( !components[ownerID]->minimized )
        {
            SDL_SetRenderDrawColor( components[ownerID]->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( components[ownerID]->renderer );
            SDL_RenderPresent( components[ownerID]->renderer );
	    glClearColor(0xFF, 0xFF, 0xFF, 0xFF);
	    glClear(GL_COLOR_BUFFER_BIT);
	    SDL_GL_SwapWindow(components[ownerID]->window);
        }
    }
}

int WindowSystem::GetWidth(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
      return components[ownerID]->width;
    }
}

int WindowSystem::GetHeight(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
        return components[ownerID]->height;
    }
}

bool WindowSystem::HasMouseFocus(EntityID ownerID)
{
  if(GetEntity(ownerID) != NULL)
  {
      return components[ownerID]->mouseFocus;
  }
}

bool WindowSystem::HasKeyboardFocus(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
      return components[ownerID]->keyboardFocus;
    }
}

bool WindowSystem::IsMinimized(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
      return components[ownerID]->minimized;
    }
}

bool WindowSystem::IsShown(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
        return components[ownerID]->shown;
    }
}

void WindowSystem::FreeWindow(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
        if(components[ownerID]->window != NULL)
        {
            SDL_DestroyWindow(components[ownerID]->window);
        }
        if(components[ownerID]->context != NULL)
	{
	    SDL_GL_DeleteContext(components[ownerID]->context); 
	}
        components[ownerID]->mouseFocus = false;
        components[ownerID]->keyboardFocus = false;
        components[ownerID]->height = 0;
        components[ownerID]->width = 0;

        r_component::Destroy(components[ownerID]);
        components.erase(ownerID);
    }
}

WindowComponent::WindowComponent()
{
    window = NULL;
    mouseFocus = false;
    keyboardFocus = false;
    fullscreen = false;
    minimized = false;
    height = 0;
    width = 0;
}


