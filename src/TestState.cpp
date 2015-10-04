#include <stdio.h>
#include "TestState.h"

TestState TestState::m_TestState;

void TestState::Init(){}
void TestState::Cleanup(){}
void TestState::Pause(){}
void TestState::Resume(){}
void TestState::HandleEvents(RGameEngine* game)
{
    getch();
    game->Quit();
}
void TestState::Update(RGameEngine* game){}
void TestState::Draw(RGameEngine* game){} 
