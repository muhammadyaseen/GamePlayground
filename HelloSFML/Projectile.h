#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Projectile
{
	sf::Sprite _sprite;
	b2Body* _pBody;
	b2BodyDef _bodyDef;
	b2PolygonShape _bodyShape;
	b2FixtureDef _fixtureDef;
	b2Vec2 _initpos;
	int _damage;
	int _direction;
	float _range;

	float distanceTravelled();

public:
	void SetWorld(b2World & world);
	bool Update(sf::Event e, sf::Time dt);
	void Draw(sf::RenderWindow& window, sf::Time dt);
	b2Body* GetPhysicsBody();
	Projectile(sf::Texture& texture, int initX, int initY, int direction);
	Projectile();
	~Projectile();

	Projectile* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }
};
