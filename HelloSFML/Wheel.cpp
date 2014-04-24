#include "Wheel.h"


Wheel::Wheel()
{
}

void Wheel::SetWorld(b2World& world)
{
	Ball::SetWorld(world);
	_pJointBody = world.CreateBody(&_jointBodyDef);
	_pJointBody->CreateFixture( &_jointFixtureDef);

	_jointDef.bodyA = _pBody;
	_jointDef.bodyB = _pJointBody; 
	_jointDef.localAnchorA = _pBody->GetLocalCenter() ;
	_jointDef.localAnchorB = _pJointBody->GetLocalCenter();

	_pJoint = (b2RevoluteJoint *)world.CreateJoint(&_jointDef);
}

Wheel::Wheel(sf::Texture& texture, float initX, float initY) 
	: Ball(texture, initX, initY )
{
	//setup joint body

	_jointBodyDef.type = b2_staticBody;
	_jointBodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) );

	_jointBodyShape.m_radius = MathHelper::ToUnit( 5.f ); //5 pixels
	
	_jointFixtureDef.density = 1.f;
	_jointFixtureDef.shape = &_jointBodyShape;

	//set up joint
	_jointDef.enableMotor = true;
	_jointDef.maxMotorTorque = 7.5f;
	_jointDef.motorSpeed = MathHelper::DegreeToRadian( 180 );
	_jointDef.collideConnected = false;
}

void Wheel::Update(sf::Event e, sf::Time dt)
{
	Ball::Update(e, dt);

}

void Wheel::Draw( sf::RenderWindow& window, sf::Time dt )
{
	Ball::Draw( window, dt );
}

