#ifndef RSPRITE_H
#define RSPRITE_H

#include <array>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "r_SDL.h"
#include "RTexture.h"

/*  
    RSprite contains functionality for handeling RTexture graphics and displaing them on screen.
*/

class RSprite
{
    public:
        void Init(RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed = 30, SDL_Color fg = {0,0,0,0}, SDL_Color bg = {0,0,0,0}, std::string animation = "DEFAULT" );
        void SetTexture(RTexture* texture);
        void AddAnimation(std::string animation, std::vector<SDL_Rect> frames); //adds animation to animation list
        void RemoveAnimation(std::string animation); //removes an animation
        void ClearAnimations(); //clears the animation map
        void PushFrames(std::string animation, std::vector<SDL_Rect> frames); // adds frames to animation
        void ClearFrames(std::string animation); //clears frames for an animation from the list
        
        void SetForeground( SDL_Color color ); // set foreground color
        void SetBackground(SDL_Color color); //set background render color
        void SetAlpha(uint8_t alpha); //sprite texture alpha
        void SetBlendMode(SDL_BlendMode blending); //set blend mode
        void SetFlipMode(SDL_RendererFlip flip); //set flip mode
        void SetCenter(SDL_Point center); //set pivot point
        void SetAngle(double angle); //set rotation angle
        
        //animation interface
        void SetAnimation(std::string animation, uint16_t frame = 0); //set current animation
        void SetAnimationSpeed(int animationSpeed);
        void SetFrame(uint16_t frame); // set current frame
        void NextFrame(); // go to next frame
        void PreviousFrame(); //go to previous frame
        void Pause();
        void Play();
        
        void UpdateAnimation(); //update animation logic
        void Render(SDL_Renderer* renderer, int x, int y); //render sprite at point
        
        RSprite();
        ~RSprite();
    
    protected:
        RTexture* _texture;
        std::map<std::string, std::vector<SDL_Rect>> _animations;
        std::string _currentAnimation;
        uint16_t _currentframe;
        int _animSpeed;
        SDL_Color _fg;
        SDL_Color _bg;
        SDL_RendererFlip _flip;
        SDL_Point _center;
        double _angle;
        
        void UpdateTexture();
        void RenderBackground(SDL_Renderer* renderer, SDL_Rect frame);
    
        void ResetAnimCounter();
    private:
        int _animCount;
        bool _paused;
};

/*  
    RUnicodeSprite has support for handeling and generating pre-rendered Unicode text and symbols
    for display on screen.
*/
class RUnicodeSprite: public RSprite
{
    public:
        //Initilizes sprite and generates internal spritesheet from an array of Unicode symbols[].
        void Init( SDL_Renderer* renderer, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, SDL_Color fg = {0xFF,0xFF,0xFF,0xFF}, SDL_Color bg = {0xFF,0xFF,0xFF,0xFF}, std::string animation = "DEFAULT", int animationSpeed = 30);
        //Initilizes sprite with external spritesheet with symbols[].
        void Init( RTexture* texture, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, SDL_Color fg = {0xFF,0xFF,0xFF,0xFF}, SDL_Color bg = {0xFF,0xFF,0xFF,0xFF}, std::string animation = "DEFAULT", int animationSpeed = 30);    
        void AddAnimation(std::string animation, std::vector<uint16_t> frames) ; //Adds an animation as a list of symbols.
        
        int GetPntSize(); //Returns font size.
        void SetPntSize(int pnt);
        int GetWidth();
        int GetHeight();
        void SetDimensions(int width, int height );//sets symbol dimensions for size calculations
       
        
        void RenderSymbol(SDL_Renderer* renderer, int x, int y, uint16_t symbol); //Renders a symbol. Renders first symbol in the sheet if symbol does not exist in the symbol list.
        void RenderSymbol(SDL_Renderer* renderer, int x, int y, std::string symbols); //Renders a string. Renders first symbol in the sheet if symbol does not exist in the symbol list.
        
        RUnicodeSprite(); 
       ~RUnicodeSprite();

    private:
        void CreateUnicodeSpriteSheet(SDL_Renderer* renderer, TTF_Font* font, std::vector<uint16_t> symbols); //Generates an internal sprite sheet from a list of symbols.
        uint16_t GetSymbolIndex(uint16_t symbol);
        int _pntsize;
        int _w, _h;
        std::vector<uint16_t> _symbols;
        bool _internalTexutreInstance; //true if Init Created its own RTexture instance. Used for cleanup.
};
#endif
