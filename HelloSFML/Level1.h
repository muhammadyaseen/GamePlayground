#pragma once
#include "state.h"
#include<vector>
#include<map>
#include <iostream>
#include <string>
#include <list>
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
#include "EntityType.cpp"
#include "Ranger.h"
#include "Score.h"





class Level1 :
	public State
{
	
private:
	
	
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


	Score *score;


public:

	Level1(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World,Score* score);
	void LoadContent();
	
	void HandleInput(Event gameEvent);

	void UnloadContent();
	 
	State::LevelState Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall);


	 
	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);



	void SpreadPickupCoins();

	void SpreadBrickPlatforms();

	void SpreadTrees();

	Level1(void);
	~Level1(void);
};

