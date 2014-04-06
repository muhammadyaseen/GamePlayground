#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "MathHelper.h"
#include "Health.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Player
{
private:
	bool _alive;
	bool _inAir;

	enum State {
		Idle, 
		Walking,bWalking, 
		Running,bRunning,
		Rising, 
		Falling,
		Landing
	};

	State _state;
	State _previousState;

	b2Body* _pBody;
	b2BodyDef _bodyDef;
	b2PolygonShape _bodyShape;
	b2FixtureDef _fixtureDef;

	std::map<State, Animation> _animationBank;
	Animation *_currentAnimation;
	AnimatedSprite _animatedSprite;
	
	std::map<State, Texture> _textureBank;
	
	void handleEvent(Event currentEvent, Event oldEvent);
	void handleState();
	void changeSprite(State);
	
public:
	Player();
	Player(Texture& texture, float initX, float initY);

	void SetWorld(b2World& world);
	void Create(Texture& texture, float initX, float initY);

	void LoadContent();
	void Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime);
	void Draw(sf::RenderWindow& window, sf::Time dt);

	State GetState();
	b2Body* GetPhysicsBody();
	bool IsAlive();
};
