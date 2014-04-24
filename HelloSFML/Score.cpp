#include "Score.h"





Score::Score(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World)
	:State(window,debugDraw,World),
	CoinsCollected(0),
	LivesLeft(3),
	totalScore(0)
	
{
}


void Score::LoadContent(){}
	
void Score::HandleInput(Event gameEvent){}

void Score::UnloadContent(){}
	 
State::LevelState Score::Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall)
{
	return LState;
}


void Score::Draw(RenderWindow& window, Time timeSinceLastDrawCall){}


void Score::IncrementScore(int x)
{
	totalScore+=x;
}
void Score::IncrementCoins()
{
	CoinsCollected++;
}
void Score::IncrementLife()
{
	LivesLeft++;
}

void Score::DecrementScore(int x)
{
	totalScore-=x;
}
void Score::DecrementCoins()
{
	CoinsCollected--;
}
void Score::DecrementLife()
{
	LivesLeft--;
}


int Score::GetLives()
{
	return LivesLeft;
}
int Score::GetScore()
{
	return totalScore;
}
int Score::GetCoins()
{
	return CoinsCollected;
}