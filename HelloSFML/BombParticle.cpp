#include <iostream>
#include "BombParticle.h"


using namespace std;

void BombParticle::SetWorld(b2World& world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);

	_gameWorld = &world;
}

BombParticle::BombParticle()
{
}

BombParticle::BombParticle(sf::Texture& texture, b2Vec2 initPoint, float blastPower, b2Vec2 angle)
{
	_sprite.setTexture( texture );
	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;
	_bodyDef.bullet = true;
	_bodyDef.linearDamping = 10;
	_bodyDef.gravityScale = 0;
	_bodyDef.position = initPoint; 
	_bodyDef.linearVelocity = blastPower * angle;	
	
	_bodyShape.m_radius = MathHelper::ToUnit( texture.getSize().x / 2.f );

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" <<  "R : " << _bodyShape.m_radius << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 60.f / 30.f;  //divided by numofrays
	_fixtureDef.friction = 0.f;
	_fixtureDef.restitution = 0.99f;
	_fixtureDef.filter.groupIndex = -1;
}

b2Body* BombParticle::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& BombParticle::GetSprite()
{
	return _sprite;
}


void BombParticle::Update(sf::Event e, sf::Time dt)
{
	//_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);
}

void BombParticle::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}

void BombParticle::CleanUp()
{
	_gameWorld->DestroyBody( _pBody );
}
