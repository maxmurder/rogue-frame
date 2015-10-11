#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class RGameState;

class RGameEngine
{
    public:
    bool Init(const char* title, int width=640, int height=480, int bbp=0, bool fullscreen=false);
    void Cleanup();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    bool Running() {return m_running;}
    void Quit() {m_running = false;}
    
    void ChangeState(RGameState*);
    void PushState(RGameState*);
    void PopState();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int GetWindowWidth();
    int GetWindowHeight();
    
    private:
    std::vector<RGameState*> states; //game state stack
    
    bool m_fullscreen;
    bool m_running;
    
    int m_window_width, m_window_height; 
};

#endif
