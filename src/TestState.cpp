#include <stdio.h>
#include "TestState.h"

TestState TestState::m_TestState;

void TestState::Init()
{
    m_image = SDL_LoadBMP( "src/test.bmp" );
}
void TestState::Cleanup()
{
    SDL_FreeSurface( m_image );
}
void TestState::Pause(){}
void TestState::Resume(){}
void TestState::HandleEvents(RGameEngine* game){}
void TestState::Update(RGameEngine* game){}
void TestState::Draw(RGameEngine* game){
    SDL_BlitSurface ( m_image, NULL, game->screen, NULL );
    SDL_Flip( game->screen );
    SDL_Delay(2000);
    game->Quit();
} 
