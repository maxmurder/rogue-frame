#ifndef RSPRITE_H
#define RSPRITE_H

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "r_SDL.h"
#include "RTexture.h"

class RSprite
{
    public:
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
        
        void UpdateAnimation(); //update animation logic
        void Render(SDL_Renderer* renderer, int x, int y); //render sprite at point
        
        RSprite(RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed = 0, SDL_Color fg = {0,0,0,0}, SDL_Color bg = {0,0,0,0}, std::string animation = "DEFAULT");
        ~RSprite();
    
    private:
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
};
#endif
