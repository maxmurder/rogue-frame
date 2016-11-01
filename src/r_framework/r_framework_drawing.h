#ifndef R_FRAMEWORK_DRAWING_H
#define R_FRAMEWORK_DRAWING_H
#include <vector>
#include "r_framework.h"
#include "r_system/r_sprite.h"
#include "r_system/r_texture.h"
#include "r_system/r_ui_text.h"
#include "r_utils/r_util_components.h"

namespace r_framework
{

    class r_framework_drawing : public RFramework {
        public:
        void Init(RGameEngine* game);
        void Pause(){};
        void Resume(){};
        void HandleEvents(){};
        void Upadte(){};
        void Draw(){};

        private:
        SpriteSystem _sys_sprite;
        TextureSystem _sys_texture;
        UITextSystem _sys_ui_text;
        System<ColorComponent> _sys_fg_color;
        System<ColorComponent> _sys_bg_color;
        System<XYZComponent> _sys_position;
        System<WHComponent> _sys_dimensions;
        System<UnicodeSymbolComponent> _sys_unicode;

        std::vector<EntityID> _entities;
    };
}
#endif