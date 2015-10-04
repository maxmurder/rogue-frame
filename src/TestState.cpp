#include <stdio.h>
#include "TestState.h"
#include "SDL/SDL.h"

TestState TestState::m_TestState;

void TestState::Init(){}
void TestState::Cleanup(){}
void TestState::Pause(){}
void TestState::Resume(){}
void TestState::HandleEvents(RGameEngine* game)
{
    SDL_Delay(2000);
    game->Quit();
}
void TestState::Update(RGameEngine* game){}
void TestState::Draw(RGameEngine* game){} 
