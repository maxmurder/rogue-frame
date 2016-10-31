#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <array>
#include <stdlib.h>
#include <assert.h>
#include "TestState.h"
#include "r_utils/r_SDL.h"
#include "r_utils/r_utils.h"
#include "r_utils/r_renderer.h"
#include "r_utils/r_lua.h"
#include "r_entity/r_message.h"
#include "r_entity/r_queue.h"
#include "r_utils/r_rng.h"

#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;

EntityID BACKGROUND_TEXTURE, UNICODE_TEXTURE, TESTTILES, TESTPLAYER, TESTTEXTURE_1, TESTTEXT, TESTTEXT2, TESTINPUT, FPSCOUNTER, FPSCOUNTERGLOBAL;
int TEST_MESSAGE = 1;

vector<EntityID> testchars;
vector<ISystem *> systemlist;

void TestState::Init(RGameEngine* game)
{
    //initilize frameworks
    _baseFramework.Init(game);
    //add Systems to the list
    systemlist.push_back(&_spriteSystem);
    systemlist.push_back(&_textureSystem);
    systemlist.push_back(&_uiTextSystem);
    systemlist.push_back(&_fgColorSystem);
    systemlist.push_back(&_bgColorSystem);
    systemlist.push_back(&_positionSystem);
    systemlist.push_back(&_velocitySystem);
    systemlist.push_back(&_dimensionsSystem);
    systemlist.push_back(&_unicodeSymbolSystem);
    systemlist.push_back(&_stringSystem);
    
    // file writing test
    string lstring = r_utils::UnicodeToHexString (UNICODE_LATIN_BASIC, ",") ;
    r_SDL::WriteFile( "data/raw/latin_basic", lstring.c_str() );

    //file read test
    LuaScript ansi("data/lua/ansi437.lua");
    vector<int> ansiVec(ansi.GetVector<int>("chars"));

    ANSI_437 = CreateEntity();
    _unicodeSymbolSystem.AddComponent(r_component::Create("UnicodeSymbolComponent", ANSI_437), ANSI_437);
    for (auto &s: ansiVec)
    {
        _unicodeSymbolSystem.components[ANSI_437]->symbols.push_back((uint16_t)s);
    }

    int pnt = 16;
    //setup font
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);

    //load background texture and everything needed to render
    BACKGROUND_TEXTURE = CreateEntity();
    _textureSystem.AddComponent(r_component::Create("TextureComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _textureSystem.LoadFromFile(BACKGROUND_TEXTURE, "data/gfx/checker.png", _baseFramework.Renderer());

    //create rendered unicode sheet for basic latin set
    UNICODE_TEXTURE = CreateEntity();
    _textureSystem.AddComponent(r_component::Create("TextureComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _textureSystem.RenderUnicode(UNICODE_TEXTURE, _baseFramework.Renderer(), _font, &_unicodeSymbolSystem.components[ANSI_437]->symbols[0]);

    //create metadata for latin set
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _dimensionsSystem.components[UNICODE_TEXTURE]->w = pnt/2;
    _dimensionsSystem.components[UNICODE_TEXTURE]->h = pnt;

    //get tileset metadata from lua file
    LuaScript tileScript("data/lua/testTiles.lua");
    int sheetw = tileScript.Get<float>("sheet.w");
    int cellw = tileScript.Get<float>("cell.w");
    int cellh = tileScript.Get<float>("cell.h");
    vector<int> tileVector(tileScript.GetVector<int>("chars"));

    //create a frame map for the tileset
    map<wchar_t, SDL_Rect> tileFrames;
    int i = 0, r = 0;
    for(auto &c : tileVector)
    {
        int x = i % ( sheetw / cellw ) * cellw;
        int y = r * cellh;
        tileFrames[c]={x, y, cellw, cellh};

        i++;
        if(i % (sheetw / cellw) == 0)
        {
            r++;
        }
    }

    //create the tileset
    TESTTILES = CreateEntity();
    _textureSystem.AddComponent(r_component::Create("TextureComponent", TESTTILES), TESTTILES);
    _textureSystem.LoadFromFile(TESTTILES, tileScript.Get<string>("file"), _baseFramework.Renderer(), {0xFF, 0x00, 0xFF, 0xFF});


    //create "player" entity
    TESTPLAYER = CreateEntity();

    _textureSystem.AddComponent(r_component::Create("TextureComponent", TESTPLAYER), TESTPLAYER);
    _textureSystem.LoadFromFile(TESTPLAYER, "data/gfx/curses_square_16x16.png", _baseFramework.Renderer(), {0xFF,0x00,0xFF,0xFF});

    _positionSystem.AddComponent(r_component::Create("XYZComponent", TESTPLAYER), TESTPLAYER);
    _positionSystem.components[TESTPLAYER]->x = _baseFramework.Dimensions().first / 2;
    _positionSystem.components[TESTPLAYER]->y = _baseFramework.Dimensions().second / 2;

    _velocitySystem.AddComponent(r_component::Create("XYZComponent", TESTPLAYER), TESTPLAYER);
    _velocitySystem.components[TESTPLAYER]->x = 0;
    _velocitySystem.components[TESTPLAYER]->y = 0;
    //create metadata
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", TESTPLAYER), TESTPLAYER);
    _dimensionsSystem.components[TESTPLAYER]->w = 8;
    _dimensionsSystem.components[TESTPLAYER]->h = 16;

    //create sprite
    _spriteSystem.AddComponent( TESTPLAYER,
                                _textureSystem.components[UNICODE_TEXTURE]->texture,
                                {(int)_positionSystem.components[TESTPLAYER]->x, (int)_positionSystem.components[TESTPLAYER]->y, _dimensionsSystem.components[TESTPLAYER]->w, _dimensionsSystem.components[TESTPLAYER]->h},
                                {0x80,0x00,0xFF,0xFF},
                                {0xBA,0xDA,0x55,0xFF});

    //load lua script
    LuaScript testScript("data/lua/test.lua");
    vector<SDL_Rect> testAnim;

    //setup test animation
    for (auto c :  testScript.GetVector<int>("animation"))
    {
        testAnim.push_back({_unicodeSymbolSystem.components[ANSI_437]->GetIndex(c) * (pnt/2), 0, pnt/2, pnt });
    }

    _spriteSystem.AddAnimation(TESTPLAYER, "TEST",testAnim);
    _spriteSystem.SetAnimation(TESTPLAYER, "TEST");
    _spriteSystem.components[TESTPLAYER]->animationSpeed = 500;

    //make map of character frames for text system
    map<wchar_t, SDL_Rect> charframes;
    for(auto &c : _unicodeSymbolSystem.components[ANSI_437]->symbols)
    {
        charframes[c]={_unicodeSymbolSystem.components[ANSI_437]->GetIndex(c) * _dimensionsSystem.components[UNICODE_TEXTURE]->w, 0, _dimensionsSystem.components[UNICODE_TEXTURE]->w, _dimensionsSystem.components[UNICODE_TEXTURE]->h};
    }

    //fps counter
    FPSCOUNTER = CreateEntity();
    _uiTextSystem.AddComponent(FPSCOUNTER,
                                _textureSystem.components[UNICODE_TEXTURE]->texture,
                                charframes,
                                {_baseFramework.Dimensions().first,0,_dimensionsSystem.components[UNICODE_TEXTURE]->w,_dimensionsSystem.components[UNICODE_TEXTURE]->h},
                                L"",
                                {0x80, 0x00, 0xFF, 0xFF},
                                {0x00, 0x00, 0x00, 0xFF});

    //fps counter
    FPSCOUNTERGLOBAL = CreateEntity();
    _uiTextSystem.AddComponent(FPSCOUNTERGLOBAL,
                                _textureSystem.components[UNICODE_TEXTURE]->texture,
                                charframes,
                                {_baseFramework.Dimensions().first,0,_dimensionsSystem.components[UNICODE_TEXTURE]->w,_dimensionsSystem.components[UNICODE_TEXTURE]->h},
                                L"",
                                {0x80, 0x00, 0xFF, 0xFF},
                                {0x00, 0x00, 0x00, 0xFF});
    
    //input test
    TESTINPUT = CreateEntity();
    _uiTextSystem.AddComponent(TESTINPUT,
				_textureSystem.components[UNICODE_TEXTURE]->texture,
				charframes,
				{_baseFramework.Dimensions().first, 0 , _dimensionsSystem.components[UNICODE_TEXTURE]->w,_dimensionsSystem.components[UNICODE_TEXTURE]->h},
				L"",
				{0x80, 0x00, 0xFF, 0xFF},
                                {0x00, 0x00, 0x00, 0xFF});


    string s = testScript.Get<string>("test.string");
    wstring ws;
    ws.assign(s.begin(), s.end());

    //test text
    TESTTEXT = CreateEntity();
    _stringSystem.AddComponent(r_component::Create("StringComponent", TESTTEXT), TESTTEXT);
    _stringSystem.components[TESTTEXT]->text = ws;
    _positionSystem.AddComponent(r_component::Create("XYZComponent",TESTTEXT), TESTTEXT);
    _positionSystem.components[TESTTEXT]->x = testScript.Get<float>("test.position.x");
    _positionSystem.components[TESTTEXT]->y = testScript.Get<float>("test.position.y");
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent",TESTTEXT), TESTTEXT);
    _dimensionsSystem.components[TESTTEXT]->w = 240;
    _dimensionsSystem.components[TESTTEXT]->h = 240;

    _uiTextSystem.AddComponent(TESTTEXT,
                                _textureSystem.components[TESTTILES]->texture,
                                tileFrames,
                                {(int)_positionSystem.components[TESTTEXT]->x,(int)_positionSystem.components[TESTTEXT]->y, _dimensionsSystem.components[TESTTEXT]->w, _dimensionsSystem.components[TESTTEXT]->h},
                                _stringSystem.components[TESTTEXT]->text,
                                {0x80, 0x00, 0xFF, 0xFF},
                                {0x00, 0x00, 0x00, 0xFF});

    //add test text elements
    TESTTEXT2 = CreateEntity();
    wstring ansistr;
    ansistr.assign(_unicodeSymbolSystem.components[ANSI_437]->symbols.begin(), _unicodeSymbolSystem.components[ANSI_437]->symbols.end());

    _uiTextSystem.AddComponent(TESTTEXT2, _textureSystem.components[UNICODE_TEXTURE]->texture, charframes, {0, 0, 128, 256}, ansistr, {0x80, 0x00, 0xFF, 0xFF}, {0x00, 0x00, 0x00, 0xFF});

    _uiTextSystem.AddComponent( TESTTILES, _textureSystem.components[TESTTILES]->texture, tileFrames, {144, 0, 256, 256}, ansistr, {0x80, 0x00, 0xFF, 0xFF}, {0x00, 0x00, 0x00, 0xFF});

    //test message
    r_frame::Queue queue;
    queue.put(r_frame::DataMessage<std::string>(1, "test"));
    auto msg = queue.get();
    auto& dmsg = dynamic_cast<r_frame::DataMessage<std::string>&>(*msg);
    cout << dmsg.getMessageId() << ":" << dmsg.getPayload() << endl;

    //test rng
    r_rng::init(r_time::system_time());
    r_rng::R_RNG* rng_eng = r_rng::engine();
    assert(rng_eng != NULL);
    cout << "seed: " << r_rng::seed() << endl;
    uniform_int_distribution<uint32_t> custom_dist(0, 10);
    cout << "custom: " << custom_dist(*rng_eng) << endl;

    cout << "rng: " << r_rng::rng() << endl;
    cout << "rng_range: " << r_rng::rng_range(0, 100) << endl;
    cout << "rng_float: " << r_rng::rng_float(0.0, 100.0) << endl;
    cout << "bern:";
    for(int i = 0; i < 10; i++)
    {
        cout << " " << r_rng::bern(0.5);
    }
    cout << endl;
    cout << "binomial: " << r_rng::binomial(10, 0.5) << endl;
    array<int, 10> bi = {};
    for(int i = 0; i < 1000; i++)
    {
        ++bi[r_rng::binomial(bi.size(), 0.5)];
    }
    for(int i = 0; i < bi.size(); i++ )
    {
        cout << i << ": " << string( bi[i]/10, '*' ) << endl;
    }
    cout << "geometric: " << r_rng::geometric(0.3) << endl;
    array<int, 10> ge = {};
    for (int i = 0; i < 1000; i++)
    {
        int num = r_rng::geometric(0.3);
        if (num < ge.size()) ++ge[num];
    }
    for (int i = 0; i < ge.size(); i++)
    {
        cout << i << ": " << string(ge[i]/10, '*') << endl;
    }
    cout << "poisson: " << r_rng::poisson(5.0) << endl;
    array<int, 10> po = {};
    for(int i = 0; i < 1000; i++)
    {
        int num = r_rng::poisson(5.0);
        if ( num < po.size() ) ++po[num]; 
    }
    for(int i = 0; i < po.size(); i++)
    {
        cout << i << ": " << string(po[i]/10, '*') << endl;
    }
    cout << "normal: " << r_rng::normal(0.0, 1.0) << endl;
    array<int, 10> no = {};
    for (int i = 0; i < 1000; i++)
    {
        double num = r_rng::normal(5.0, 1.0);
        if (( num >= 0.0 ) && ( num <= 10.0))
            ++no[int(num)];
    }
    for(int i = 0; i < no.size(); i++)
    {
        cout << i << "-" << (i+1) << ": ";
        cout << std::string(no[i]/10, '*') << endl;
    }
    cout << "exponential: " << r_rng::exponential(3.5) << endl;
    int p = cout.precision();
    cout << fixed; cout.precision(1);
    array<int, 10> ex = {};
    for(int i =  0; i < 1000; i++)
    {
        double num = r_rng::exponential(3.5);
        if (num < 1.0) ++ex[int(ex.size()*num)];
    }
    for(int i = 0; i < ex.size(); i++)
    {
        cout << float(i)/ex.size() << "-" << float(i+1)/ex.size() << ": ";
        cout << string(ex[i]/10, '*') << endl;
    }
    cout << "dice: " << r_rng::dice(1, 6) << endl;
    resetiosflags; cout.precision(p);

    //randomize player velocity
    _velocitySystem.components[TESTPLAYER]->x = r_rng::normal(250.0, 1.0) * _baseFramework.Time()->Delta();
    _velocitySystem.components[TESTPLAYER]->y = r_rng::normal(0.0,100.0) * _baseFramework.Time()->Delta();

    //finishing up
    TTF_CloseFont(_font);
    game->UPDATE_MS = testScript.Get<float>("framerate");
}

void TestState::Cleanup(RGameEngine* game)
{
    _baseFramework.Cleanup();
    for( auto c : systemlist)
    {
        c->Cleanup();
    }
    systemlist.clear();
}

void TestState::Pause(RGameEngine* game){}
void TestState::Resume(RGameEngine* game){}
int TestState::HandleEvents(RGameEngine* game)
{
    _baseFramework.HandleEvents(game);
    
    static bool sp_down;
    if ( _baseFramework.Keystates()[SDL_SCANCODE_SPACE] )
    {
        if(!sp_down)
        {
            static bool der;
            if (der)
            {
                der = false;
            }else
            {
                der = true;
            }
        }
        sp_down = true;
    }else{
        sp_down = false;
    }
    if ( _baseFramework.MouseState().LB )
    {
      _positionSystem.components[TESTPLAYER]->x = _baseFramework.MouseState().x;
      _positionSystem.components[TESTPLAYER]->y = _baseFramework.MouseState().y;
    }
    
    if (  _baseFramework.Keystates()[SDL_SCANCODE_UP] )
    {
        _velocitySystem.components[TESTPLAYER]->y -= 1000 * game->GlobalDelta();
    }
    if (  _baseFramework.Keystates()[SDL_SCANCODE_DOWN] )
    {
        _velocitySystem.components[TESTPLAYER]->y += 1000 * game->GlobalDelta();
    }
    if (  _baseFramework.Keystates()[SDL_SCANCODE_LEFT] )
    {
        _velocitySystem.components[TESTPLAYER]->x -= 1000 * game->GlobalDelta();
    }
    if (  _baseFramework.Keystates()[SDL_SCANCODE_RIGHT] )
    {
        _velocitySystem.components[TESTPLAYER]->x += 1000 * game->GlobalDelta();
    }
    return 0;
}

int TestState::Update(RGameEngine* game)
{
    //update local time
    _baseFramework.Time()->Update();

    //update sprite animations
    _spriteSystem.Update(game->UPDATE_MS);

    //apply vleocity
    for(auto &c : _velocitySystem.components)
    {
        if(GetEntity(c.second->ownerID)!=NULL)
        {
            _positionSystem.components[c.first]->x += c.second->x * game->FixedUpdateDelta();
            _positionSystem.components[c.first]->y += c.second->y * game->FixedUpdateDelta();
        }
    }

    //keep player in bounds
    if( _positionSystem.components[TESTPLAYER]->x > _baseFramework.Dimensions().first - _dimensionsSystem.components[TESTPLAYER]->w)
    {
        _velocitySystem.components[TESTPLAYER]->x = -1 * fabs(_velocitySystem.components[TESTPLAYER]->x);
    }else if ( _positionSystem.components[TESTPLAYER]->x < 0)
    {
        _velocitySystem.components[TESTPLAYER]->x = fabs(_velocitySystem.components[TESTPLAYER]->x);
    }
    if( _positionSystem.components[TESTPLAYER]->y > _baseFramework.Dimensions().second - _dimensionsSystem.components[TESTPLAYER]->h)
    {
        _velocitySystem.components[TESTPLAYER]->y = -1 * fabs(_velocitySystem.components[TESTPLAYER]->y);
    }else if ( _positionSystem.components[TESTPLAYER]->y < 0)
    {
        _velocitySystem.components[TESTPLAYER]->y = fabs(_velocitySystem.components[TESTPLAYER]->y);
    }

    //update sprite position
    _spriteSystem.components[TESTPLAYER]->dimensions.x = _positionSystem.components[TESTPLAYER]->x;
    _spriteSystem.components[TESTPLAYER]->dimensions.y = _positionSystem.components[TESTPLAYER]->y;

    return 0;
}

int TestState::Draw(RGameEngine* game)
{
    wstringstream msg;
    msg.precision(2);
    msg << L"TPS: " << fixed << 1/_baseFramework.Time()->Delta() << L" FTPS: " << 1/game->FixedUpdateDelta() << L" MS: " << _baseFramework.Time()->ElapsedTime();
    _uiTextSystem.SetText(FPSCOUNTER, msg.str());
    int wid = _dimensionsSystem.components[UNICODE_TEXTURE]->w * msg.str().length();
    _uiTextSystem.SetDisplayRect(FPSCOUNTER, { _baseFramework.Dimensions().first - wid, 0, wid, _dimensionsSystem.components[UNICODE_TEXTURE]->h});

    msg.str(L"");
    msg << L"FPS: " << fixed << 1/game->GlobalDelta() << L" MS: " << fixed << game->GlobalMS();
    _uiTextSystem.SetText(FPSCOUNTERGLOBAL, msg.str());
    wid = _dimensionsSystem.components[UNICODE_TEXTURE]->w * msg.str().length();
    _uiTextSystem.SetDisplayRect(FPSCOUNTERGLOBAL, { _baseFramework.Dimensions().first - wid, _dimensionsSystem.components[UNICODE_TEXTURE]->h, wid, _dimensionsSystem.components[UNICODE_TEXTURE]->h});

    msg.str(L"");
    wstring wsTemp(_baseFramework.Input()->begin(),_baseFramework.Input()->end());
    msg << wsTemp;
    _uiTextSystem.SetText(TESTINPUT, msg.str());
    wid = msg.str().length() < 25 ? _dimensionsSystem.components[UNICODE_TEXTURE]->w * msg.str().length() : _dimensionsSystem.components[UNICODE_TEXTURE]->w * 25;
    _uiTextSystem.SetDisplayRect(TESTINPUT, {0 , ( _baseFramework.Dimensions().second / 2 ) + _dimensionsSystem.components[UNICODE_TEXTURE]->h, wid, _dimensionsSystem.components[UNICODE_TEXTURE]->h});
    
    //invoke render systems
    _uiTextSystem.Render();
    _spriteSystem.Render();

    //draw the background
    r_renderer::AddToQueue(_textureSystem.components[BACKGROUND_TEXTURE]->texture,{0,0,640,480},{0,0,640,480});

    _baseFramework.Draw();

    return 0;
}
