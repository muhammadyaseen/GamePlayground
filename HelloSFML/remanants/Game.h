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
#include "CollisionListener.h"


using namespace std;
using namespace sf;

class Game
{

public:
	Game(RenderWindow& w, SFMLDebugDraw& debugDraw);//, CollisionListener& listener);

	//Game();

	bool Run();

	/*
		For the sake of a basic 'functionality' demo, we have (or will) declare GameActors and other related
		content as class level variables

		Ideally this Game class should be inherited and game-specific actors be declared in that derived class

	*/

	const float timeStep;

	Event e;
	Event oldEvent;

	CollisionListener gameEventListener;
	b2World		*_pWorld;

	RenderWindow& _rWindow;
	SFMLDebugDraw& _rSfmlDebugDraw;

	map<std::string, sf::Texture> textureBank;

	vector<Ball> balls;
	vector<Box> boxes;
	vector<StaticPlatform> platforms;
	vector<Bomb> bombs;

	vector<JointPlatform> jointPlatforms;
	vector<Wheel> wheels;
	vector<SwingSpikeBall> spikeChains;
	Coin pickupCoin;

	vector<Coin*> coins; //for some (yet unknown) reasons it is not working with object, so I am using pointer-to-object

	Player Edward;
	Clock frameClock;
	Ranger enemy;

	View levelView;
	View hudView;

	int cameraCenter; //for debugging view

protected:

	void Initialize();

	void LoadContent();
	
	void HandleInput(Event gameEvent);

	void UnloadContent();
	 
	void Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall);
	 
	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);

	void SpreadPickupCoins();

	void SpreadBrickPlatforms();

	void SpreadTrees();

};

