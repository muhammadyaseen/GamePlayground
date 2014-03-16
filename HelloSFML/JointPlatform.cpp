#include "JointPlatform.h"
#include <iostream>

using namespace std;

JointPlatform::JointPlatform()
{
}

void JointPlatform::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);

	_pBody->CreateFixture(&_fixtureDef);






	_pJoint = (b2RevoluteJoint *)world.CreateJoint(&_jointDef);
}



JointPlatform::JointPlatform(float w, float h)
{

}

JointPlatform::JointPlatform(sf::Texture& texture, float initX, float initY, float rotation)
{
	_sprite.setTexture( texture );	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setRotation( rotation );

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 
	_bodyDef.angle = MathHelper::DegreeToRadian( rotation );
	_bodyDef.type = b2_dynamicBody;
	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.5f;

	//setup joint body

	_jointBodyDef.type = b2_staticBody;
	_jointBodyDef.position.Set(MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) );


	//set up joint

	_jointDef.collideConnected = false;
	_jointDef.bodyA = _pBody;
	_jointDef.bodyB = _pJointBody; 

}


b2Body* JointPlatform::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& JointPlatform::GetSprite()
{
	return _sprite;
}


void JointPlatform::Update(sf::Event e, sf::Time dt)
{
	_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);
}

void JointPlatform::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}


