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
        enum TextMode {NONE = 0, TEXT = 1,  UNICODE = 2, UTF8 = 3};
        //Initilizes sprite using supplied texture;
        void Init(RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed = 30, SDL_Color fg = {0x00,0x00,0x00,0xFF}, SDL_Color bg = {0x00,0x00,0x00,0x00}, std::string animation = "DEFAULT" );
        //Initilizes sprite and generates internal spritesheet from an array of Unicode symbols[].
        void Init( SDL_Renderer* renderer, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, int mode = 1, SDL_Color fg = {0xFF,0xFF,0xFF,0xFF}, SDL_Color bg = {0xFF,0xFF,0xFF,0xFF}, std::string animation = "DEFAULT", int animationSpeed = 30);
        //Initilizes sprite with external unicode/text spritesheet contining symbols[].
        void Init( RTexture* texture, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, int mode = 1, SDL_Color fg = {0xFF,0xFF,0xFF,0xFF}, SDL_Color bg = {0xFF,0xFF,0xFF,0xFF}, std::string animation = "DEFAULT", int animationSpeed = 30);    
        
        //data setting
        void SetTexture(RTexture* texture);
        void AddAnimation(std::string animation, std::vector<SDL_Rect> frames); //adds animation to animation list
        void AddUnicodeAnimation(std::string animation, std::vector<uint16_t> frames) ; //Adds an animation as a list of symbols.
        void RemoveAnimation(std::string animation); //removes an animation
        void ClearAnimations(); //clears the animation map
        void PushFrames(std::string animation, std::vector<SDL_Rect> frames); // adds frames to animation
        void ClearFrames(std::string animation); //clears frames for an animation from the list
        
        //property getting/setting
        void SetForeground( SDL_Color color ); // set foreground color
        void SetBackground(SDL_Color color); //set background render color
        void SetAlpha(uint8_t alpha); //sprite texture alpha
        void SetBlendMode(SDL_BlendMode blending); //set blend mode
        void SetFlipMode(SDL_RendererFlip flip); //set flip mode
        void SetCenter(SDL_Point center); //set pivot point
        void SetAngle(double angle); //set rotation angle
        void SetRenderOffset(int xOffset, int yOffset); //sprite render offset (for centering sprites)
        void SetDimensions(int width, int height );//sets symbol dimensions for size calculations
        
        int GetWidth();
        int GetHeight();
        int GetRenderOffsetx();
        int GetRenderOffsety();
        
        //text
        int GetPntSize(); //Returns font size.
        void SetTextMode(int mode, int pntsize  = 0); //resizes sprite based on TTF_SizeText|TTF_SizeUNICODE|TTF_SizeUTF8.
      
        //animation interface
        void SetAnimation(std::string animation, uint16_t frame = 0); //set current animation
        void SetAnimationSpeed(int animationSpeed);
        void SetFrame(uint16_t frame); // set current frame
        void NextFrame(); // go to next frame
        void PreviousFrame(); //go to previous frame
        void Pause();
        void Play();

        void UpdateAnimation(); //update animation logic
        void Render(SDL_Renderer* renderer, int x, int y); //render sprite at point using current animation
       
        //render sprite using a string or unicode symbol
        void RenderSymbol(SDL_Renderer* renderer, int x, int y, uint16_t symbol); //Renders a symbol. Renders first symbol in the sheet if symbol does not exist in the symbol list.
        void RenderSymbol(SDL_Renderer* renderer, int x, int y, std::string symbols, int width = 0); //Renders a string. Renders first symbol in the sheet if symbol does not exist in the symbol list.      
        void RenderSymbol(SDL_Renderer* renderer, int x, int y, std::vector<uint16_t> symbols, int width = 0); //Renders a string. Renders first symbol in the sheet if symbol does not exist in the symbol list.      
    
        RSprite();
        ~RSprite();
        
    protected:
        RTexture* _texture;
        std::map<std::string, std::vector<SDL_Rect>> _animations;
        std::string _currentAnimation;
        uint16_t _currentframe;
        int _animSpeed;
        int _w, _h; // width and height of sprite background
        int _cell_h, _cell_w; // cell dimensions of spritesheet 
        int _xRenderOffset, _yRenderOffset; // render offset for texture relative to the background
        SDL_Color _fg;
        SDL_Color _bg;
        SDL_RendererFlip _flip;
        SDL_Point _center;
        double _angle;
        
        void UpdateTexture();
        void RenderBackground(SDL_Renderer* renderer, SDL_Rect frame);
    
        void ResetAnimCounter();
        int _animCount;
        bool _paused;
        
        //text properties
        int _pntsize;
        std::vector<uint16_t> _symbols;
        bool _internalTexutreInstance = false; //true if Init Created its own RTexture instance. Used for cleanup.
    
        void CreateUnicodeSpriteSheet(SDL_Renderer* renderer, TTF_Font* font, std::vector<uint16_t> symbols); //Generates an internal sprite sheet from a list of symbols.
        void CalculateOffset(int *xOffset, int *yOffset, int *r, int width, int c); //calculates offsets for rendering text. 'r' is # of newlines, 'c' is number of charaters. 
        uint16_t GetSymbolIndex(uint16_t symbol);
};
#endif
