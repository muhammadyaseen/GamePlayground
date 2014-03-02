//box.cpp file
#include <iostream>
#include "Ball.h"

using namespace std;

void Ball::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

Ball::Ball()
{
}

Ball::Ball(float radius)
{
}

Ball::Ball(sf::Texture& texture, float initX, float initY)
{
	_sprite.setTexture( texture );
	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 

	_bodyDef.type = b2_dynamicBody;
	
	_bodyShape.m_radius = MathHelper::ToUnit( texture.getSize().x / 2.f );

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.5f;

}

b2Body* Ball::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& Ball::GetSprite()
{
	return _sprite;
}


void Ball::Update(sf::Event e, sf::Time dt)
{
	_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);

	//cout << "( " << MathHelper::ToPixel( _pBody->GetPosition().x ) << " , " <<
	//MathHelper::ToPixel( _pBody->GetPosition().y ) << " )";
}

void Ball::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}
