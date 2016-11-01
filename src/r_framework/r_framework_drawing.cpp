#include "r_framework_drawing.h"
namespace r_framework
{

    void r_framework_drawing::Init(RGameEngine* game)
    {  
        AddSystem(&_sys_sprite);
        systems.push_back(&_sys_ui_text);
        systems.push_back(&_sys_fg_color);
        systems.push_back(&_sys_bg_color);
        systems.push_back(&_sys_position);
        systems.push_back(&_sys_dimensions);
        systems.push_back(&_sys_unicode);
    }
}