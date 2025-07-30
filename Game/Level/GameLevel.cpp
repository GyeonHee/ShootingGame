#include "GameLevel.h"
#include "Actor/Player.h"

GameLevel::GameLevel()
{
	// 플레이어 추가
	AddActor(new Player());
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void GameLevel::Render()
{
	super::Render();
}
