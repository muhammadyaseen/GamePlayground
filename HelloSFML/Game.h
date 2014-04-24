#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Box.h"
#include "Bomb.h"
#include "Wheel.h"
#include "StaticPlatform.h"
#include "JointPlatform.h"
#include "SFMLDebugDraw.h"
#include "SwingSpikeBall.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Ranger.h"
#include "State.h"
#include "Level1.h"
#include "Score.h"
#include "CollisionListener.h"

using namespace std;
using namespace sf;

class Game
{

	enum GameState
	{
		Splash,
		Load_Screen,
		Controls,
		Credits,
		Menu,
		Level_1,
		Level_2,
		ScoreBoard,
		Exit
	};


public:


	Game(RenderWindow& w, SFMLDebugDraw& debugDraw);

	//Game();

	bool Run();

	const float timeStep;

	Event e;
	Event oldEvent;

	b2World		*_pWorld;

	RenderWindow& _rWindow;
	SFMLDebugDraw& _rSfmlDebugDraw;
	CollisionListener gameEventListener;

	GameState stateName;
	
	State* _currentState;

	View WindowView;

	Score *score;
	
protected:

	void Initialize();

	void LoadContent();
	
	void HandleInput(Event gameEvent);

	void HandleState(State::LevelState lState);

	void UnloadContent();
	 
	void Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall);
	 
	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);


	void SplashScreen();


	void LoadScreen();

	void ExitScreen();

};

