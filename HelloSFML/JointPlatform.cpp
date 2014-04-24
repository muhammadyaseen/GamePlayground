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

	_pJointBody = world.CreateBody(&_jointBodyDef);
	_pJointBody->CreateFixture( &_jointFixtureDef);

	_jointDef.bodyA = _pBody;
	_jointDef.bodyB = _pJointBody; 
	_jointDef.localAnchorA = _pBody->GetLocalCenter();
	_jointDef.localAnchorB = _pJointBody->GetLocalCenter();

	_pJoint = (b2RevoluteJoint *)world.CreateJoint(&_jointDef);
}



JointPlatform::JointPlatform(float w, float h)
{

}

JointPlatform::JointPlatform(sf::Texture& texture, sf::Texture& jointTexture, float initX, float initY, float rotation)
{
	_sprite.setTexture( texture );	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setRotation( rotation );

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 
	_bodyDef.angle = MathHelper::DegreeToRadian( rotation );
	_bodyDef.type = b2_dynamicBody;
	//_bodyDef.angularDamping = 1;
	
	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);


	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 10.f;
	_fixtureDef.friction = 0.8f;
	_fixtureDef.restitution = 0.5f;

	//texture for the acnhor or joint
	_jointBodySprite.setTexture( jointTexture );	
	_jointBodySprite.setOrigin( jointTexture.getSize().x / 2.f, jointTexture.getSize().y / 2.f);
	_jointBodySprite.setRotation( 0.0f );

	//setup joint body

	_jointBodyDef.type = b2_staticBody;
	_jointBodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) );

	_jointBodyShape.m_radius = MathHelper::ToUnit( jointTexture.getSize().x / 2.f );
	
	_jointFixtureDef.density = 1.f;
	_jointFixtureDef.shape = &_jointBodyShape;

	//set up joint
	_jointDef.enableMotor = true;
	_jointDef.maxMotorTorque = 15;
	_jointDef.motorSpeed = MathHelper::DegreeToRadian( 360 );
	_jointDef.collideConnected = false;
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

	_jointBodySprite.setRotation( MathHelper::RadianToDegree( _pJointBody->GetAngle() ) );

	_jointBodySprite.setPosition(
			MathHelper::ToPixel( _pJointBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pJointBody->GetPosition().y ) 
		);
}

void JointPlatform::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
	window.draw( _jointBodySprite );
}


