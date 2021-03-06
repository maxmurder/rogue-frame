#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "r_utils/r_SDL.h"
#include "r_engine/r_gamestate.h"
#include "r_entity/r_entity.h"
#include "r_engine/r_time.h"
#include "r_utils/r_util_components.h"
#include "r_system/r_sprite.h"
#include "r_system/r_texture.h"
#include "r_system/r_ui_text.h"
#include "r_system/r_window.h"
#include "r_framework/r_framework_base.h"

class TestState: public RGameState {

	//frameworks
	r_framework::r_framework_base _baseFramework;
        //component systems
        SpriteSystem _spriteSystem;
        TextureSystem _textureSystem;
        UITextSystem _uiTextSystem;
        System<ColorComponent> _fgColorSystem;
        System<ColorComponent> _bgColorSystem;
        System<XYZComponent> _positionSystem;
        System<XYZComponent> _velocitySystem;
        System<WHComponent> _dimensionsSystem;
        System<UnicodeSymbolComponent> _unicodeSymbolSystem;
        System<StringComponent> _stringSystem;

    public:
        void Init(RGameEngine* game);
        void Cleanup(RGameEngine* game);

        void Pause(RGameEngine* game);
        void Resume(RGameEngine* game);

        int HandleEvents(RGameEngine* game);
        int Update(RGameEngine* game);
        int Draw(RGameEngine* game);

        TestState() { }

    private:
        EntityID ANSI_437;
        EntityID SPRITE_LATIN_UNI;
        EntityID SPRITE_LATIN_TEXT;

        TTF_Font* _font;

        std::vector<uint16_t> UNICODE_LATIN_BASIC { {0x0020,0x0021,0x0022,0x0023,0x0024,0x0025,0x0026,0x0027,0x0028,0x0029,0x002a,0x002b,0x002c,0x002d,0x002e,0x002f,0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,0x0039,0x003a,0x003b,0x003c,0x003d,0x003e,0x003f,0x0040,0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,0x0048,0x0049,0x004a,0x004b,0x004c,0x004d,0x004e,0x004f,0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,0x0058,0x0059,0x005a,0x005b,0x005c,0x005d,0x005e,0x005f,0x0060,0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,0x0068,0x0069,0x006a,0x006b,0x006c,0x006d,0x006e,0x006f,0x0070,0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,0x0078,0x0079,0x007a,0x007b,0x007c,0x007d,0x007e} };
        std::vector<uint16_t> _latin;
};

#endif
