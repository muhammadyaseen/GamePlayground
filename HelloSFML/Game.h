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
#include "StaticPlatform.h"
#include "JointPlatform.h"
#include "SFMLDebugDraw.h"

using namespace std;
using namespace sf;

class Game
{

public:
	Game(RenderWindow& w, SFMLDebugDraw& debugDraw);

	//Game();

	bool Run();

	/*
		For the sake of a basic 'functionality' demo, we have (or will) declare GameActors and other related
		content as class level variables

		Ideally this Game class should be inherited and game-specific actors be declared in that derived class

	*/

	const float timeStep;

	b2World		*_pWorld;

	RenderWindow& _rWindow;
	SFMLDebugDraw& _rSfmlDebugDraw;

	map<std::string, sf::Texture> textureBank;

	vector<Ball> balls;
	vector<Box> boxes;
	vector<StaticPlatform> platforms;
	vector<Bomb> bombs;

	vector<JointPlatform> jointPlatforms;

protected:

	void Initialize();

	void LoadContent();
	
	void HandleInput(Event gameEvent);

	void UnloadContent();
	 
	void Update(Event gameEvent, Time timeSinceLastUpdateCall);
	 
	void Draw(RenderWindow& window, Time timeSinceLastDrawCall);

};

