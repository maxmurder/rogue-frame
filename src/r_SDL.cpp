#include <iostream>
#include "SDL2/SDL_image.h"
#include "r_SDL.h"

using namespace std;

SDL_Surface* r_SDL::LoadSurface( std::string path )
{
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load( path.c_str() );
    
    if( loadedSurface == NULL)
    {
        cout << "Unable to load image: " << path << " :: " << SDL_GetError() << "\n";
    }
    return loadedSurface;
}

SDL_Surface* r_SDL::LoadSurface( std::string path, int red, int green, int blue )
{
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load( path.c_str() );
    
    if( loadedSurface == NULL)
    {
        cout << "Unable to load image: " << path << " :: " << SDL_GetError() << "\n";
    } else 
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue) );
    }
    return loadedSurface;
}

SDL_Surface* r_SDL::LoadSurface( std::string path, SDL_PixelFormat* format )
{
    SDL_Surface* loadedSurface = NULL;
    SDL_Surface* optimisedSurface = NULL;
    
    loadedSurface = IMG_Load( path.c_str() );
    
    if( loadedSurface == NULL)
    {
        cout << "Unable to load image: " << path << " :: " << SDL_GetError() << "\n";
    } else 
    {
        optimisedSurface = SDL_ConvertSurface( loadedSurface, format, 0);
        if( optimisedSurface == NULL)
        {
            cout << "Unable to convert surface: " << path << " :: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface( loadedSurface );
    }
    return optimisedSurface;
}

SDL_Texture* r_SDL::LoadTexture( std::string path, SDL_Renderer* renderer )
{
    SDL_Texture* loadedTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    
    loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL )
    {
        cout << "Unable to load image: " << path << " :: " << IMG_GetError() << "\n";
    }else
    {
        loadedTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( loadedTexture == NULL )
        {
            cout << "Unable to load texture: " << path << " :: " << SDL_GetError() << "\n";
        }
        
        SDL_FreeSurface( loadedSurface );
    }
    
    return loadedTexture;
}

SDL_Texture* r_SDL::LoadTexture( std::string path, SDL_Renderer* renderer, int red, int green, int blue )
{
    SDL_Texture* loadedTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    
    loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL )
    {
        cout << "Unable to load image: " << path << " :: " << IMG_GetError() << "\n";
    }else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue) );
        loadedTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( loadedTexture == NULL )
        {
            cout << "Unable to load texture: " << path << " :: " << SDL_GetError() << "\n";
        }
        
        SDL_FreeSurface( loadedSurface );
    }
    
    return loadedTexture;
}

SDL_Texture* r_SDL::RenderText( std::string string, TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor, SDL_Texture* texture)
{
    //free texture
    if (texture != NULL) 
    {
        SDL_DestroyTexture (texture);
    }
    
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, string.c_str(), textColor );
    if (textSurface == NULL )
    {
        cout << "Unable to render text: " << string << " :: " << SDL_GetError() << "\n";
    }else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if (texture == NULL)
        {
            cout << "Unable to create texture from rendered text surface: " << string << " :: " << SDL_GetError() << "\n";  
        }
        SDL_FreeSurface(textSurface);
    }
    return texture;
}

TTF_Font* r_SDL::LoadFont( std::string path, int pointSize )
{
    TTF_Font* font = TTF_OpenFont( path.c_str(), pointSize);
    if (font == NULL )
    {
        cout << "Unable to load font: " << path << " :: " << TTF_GetError() << "\n";    
    }
    return font;
}

void r_SDL::ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
}
