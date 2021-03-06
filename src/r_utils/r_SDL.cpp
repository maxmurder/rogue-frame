#include "SDL2/SDL_image.h"
#include "r_SDL.h"
#include "r_logging.h"

char* r_SDL::ReadFile(const char* filename, int* size)
{
    //open file
    SDL_RWops *file = SDL_RWFromFile(filename, "rb");

    if( file == NULL )
    {
        R_LOG(r_logging::ERROR) << "Could not load file: " << filename << " :: " << SDL_GetError();
        return NULL;
    }

    //allocate memory
    Sint64 data_size = SDL_RWsize(file);
    char *reserved = (char*)malloc( data_size + 1 );

    //initilize buffer
    Sint64 read_total = 0, bits_read = 1;
    char *buf = reserved;

    //read data to buffer
    while (read_total < data_size && bits_read != 0)
    {
        bits_read = SDL_RWread( file, buf, 1, (data_size - read_total) );
        read_total += bits_read;
        buf += bits_read;
    }

    //close file
    SDL_RWclose(file);

    //check that correct # of bits were read
    if( read_total != data_size )
    {
        free( reserved );
        return NULL;
    }

    //add an escape
    reserved[read_total] = '\0';

    // set size
    if (size != NULL)
    {
        *size = read_total;
    }

    return reserved;
}

bool r_SDL::WriteFile (const char* filename, const char* data)
{
    //open file
    SDL_RWops *file = SDL_RWFromFile(filename, "wb");
    if( file == NULL )
    {
        R_LOG(r_logging::ERROR) << "Could not create/open file: " << filename << " :: " << SDL_GetError();
        return false;
    }else
    {
        uint32_t len = SDL_strlen(data);
        if( SDL_RWwrite( file, data, 1, len) != len)
        {
            R_LOG(r_logging::ERROR) << "Did not fully write data to: " << filename << " :: " << SDL_GetError();
        }
        SDL_RWclose( file );
    }
    return true;
}

SDL_Surface* r_SDL::LoadSurface( std::string path )
{
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL)
    {
        R_LOG(r_logging::ERROR) << "Unable to load image: " << path << " :: " << SDL_GetError();
    }
    return loadedSurface;
}

SDL_Surface* r_SDL::LoadSurface( std::string path, int red, int green, int blue )
{
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL)
    {
        R_LOG(r_logging::ERROR) << "Unable to load image: " << path << " :: " << SDL_GetError();
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
        R_LOG(r_logging::ERROR) << "Unable to load image: " << path << " :: " << SDL_GetError();
    } else
    {
        optimisedSurface = SDL_ConvertSurface( loadedSurface, format, 0);
        if( optimisedSurface == NULL)
        {
            R_LOG(r_logging::ERROR) << "Unable to convert surface: " << path << " :: " << SDL_GetError();
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
        R_LOG(r_logging::ERROR) << "Unable to load image: " << path << " :: " << IMG_GetError();
    }else
    {
        loadedTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( loadedTexture == NULL )
        {
            R_LOG(r_logging::ERROR) << "Unable to load texture: " << path << " :: " << SDL_GetError();
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
        R_LOG(r_logging::ERROR) << "Unable to load image: " << path << " :: " << IMG_GetError();
    }else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue) );
        loadedTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( loadedTexture == NULL )
        {
            R_LOG(r_logging::ERROR) << "Unable to load texture: " << path << " :: " << SDL_GetError();
        }
        SDL_FreeSurface( loadedSurface );
    }
    return loadedTexture;
}

SDL_Texture* r_SDL::RenderText( std::string string, TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color color)
{
    //free texture
    if (texture != NULL)
    {
        SDL_DestroyTexture (texture);
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, string.c_str(), color );
    if (textSurface == NULL )
    {
       R_LOG(r_logging::ERROR) << "Unable to render text: " << string << " :: " << SDL_GetError();
    }else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if (texture == NULL)
        {
            R_LOG(r_logging::ERROR) << "Unable to create texture from rendered text surface: " << string << " :: " << SDL_GetError();
        }
        SDL_FreeSurface(textSurface);
    }
    return texture;
}

SDL_Texture* r_SDL::RenderUnicode( uint16_t symbols[], TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color color)
{
    //free texture
    if (texture != NULL)
    {
        SDL_DestroyTexture (texture);
    }
    //render characters
    SDL_Surface* textSurface = TTF_RenderUNICODE_Blended( font, symbols, color );
    if (textSurface == NULL )
    {
        R_LOG(r_logging::ERROR) << "Unable to render text: " << symbols << " :: " << SDL_GetError();
    }else
    {
        //create texture
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if (texture == NULL)
        {
            R_LOG(r_logging::ERROR) << "Unable to create texture from rendered text surface: " << symbols << " :: " << SDL_GetError();
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
        R_LOG(r_logging::ERROR) << "Unable to load font: " << path << " :: " << TTF_GetError();
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

std::string r_SDL::TextInputHandler(SDL_Event &event, std::string inputString)
{
    if ( event.type == SDL_KEYDOWN )
    {
        if( event.key.keysym.sym == SDLK_BACKSPACE && inputString.length() > 0 )
        {
            inputString.pop_back();
        } else if( event.key.keysym.sym == SDLK_RETURN )
        {
            inputString.push_back(0x000D);
        }else if ( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( inputString.c_str() );
        } else if ( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            inputString = SDL_GetClipboardText();
        }
    } else if ( event.type == SDL_TEXTINPUT )
    {
        if( !( ( event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' && event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL ) )
        {
            inputString += event.text.text;
        }
    }
    return inputString;
}
