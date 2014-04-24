#pragma once
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class Coin
{

	
private:
	AnimatedSprite	_coinSprite;
	Animation		_animSequence;
	///sf::Sprite		_cointTest;
	bool isCollected;

	b2Body* _pBody;
   b2BodyDef _bodyDef;
   b2PolygonShape _bodyShape;
   b2FixtureDef _fixtureDef;

public:
	Coin();
	void Create(sf::Texture& coinTexture, float x, float y);
	~Coin();

	void Update(sf::Event e, sf::Time dt);

	void Draw( sf::RenderWindow& window, sf::Time dt );

	sf::Sprite& GetSprite();

	Coin* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }


};

