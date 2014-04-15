#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "MathHelper.h"
#include "Health.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class GameCharacter
{
protected:
	bool _alive;
	bool _movingForward;

	b2Body* _pBody;
	b2BodyDef _bodyDef;
	b2PolygonShape _bodyShape;
	b2FixtureDef _fixtureDef;

	Animation *_currentAnimation;
	AnimatedSprite _animatedSprite;

	virtual float distanceFromBody(b2Body* body)
	{
		float diff_x = _pBody->GetPosition().x - body->GetPosition().x;
		float diff_y = _pBody->GetPosition().y - body->GetPosition().y;

		return sqrt(diff_x*diff_x + diff_y*diff_y);
	}

public:
	void SetWorld(b2World & world)
	{
		_pBody = world.CreateBody(&_bodyDef);
		_pBody->CreateFixture(&_fixtureDef);
	}

	virtual void LoadContent() = 0;

	virtual void Draw(sf::RenderWindow& window, sf::Time dt)
	{
		window.draw(_animatedSprite);
	}
};

