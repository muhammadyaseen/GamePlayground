#pragma once
#include "SFMLDebugDraw.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
using namespace sf;
class State
{


public: 
	enum LevelState{
		Playing,
		Complete,
		Lost
	};
protected:
	const float timeStep;
	
	

	b2World		*_pWorld;

	RenderWindow& _rWindow;
	SFMLDebugDraw& _rSfmlDebugDraw;
	LevelState LState;
public:
	
	

	virtual void LoadContent()=0;
	
	virtual void HandleInput(Event gameEvent)=0;

	virtual void UnloadContent()=0;
	 
	virtual LevelState Update(Event gameEvent, Event prevEvent, Time timeSinceLastUpdateCall)=0;
	 
	virtual void Draw(RenderWindow& window, Time timeSinceLastDrawCall)=0;

	State(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World);

	State(void);
	~State(void);
};

