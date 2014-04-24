#include "SwingSpikeBall.h"
#include <iostream>

using namespace std;

SwingSpikeBall::SwingSpikeBall()
{
}

void SwingSpikeBall::SetWorld(b2World& world)
{
	//spikeBall.SetWorld(world);
	spikeBall.SetWorld(world);

	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
	_pBody->SetUserData( this );

	_pJointBody = world.CreateBody(&_jointBodyDef);
	_pJointBody->CreateFixture( &_jointFixtureDef);


	_chainJointDef.bodyA = _pBody;
	_chainJointDef.bodyB = _pJointBody; 
	_chainJointDef.localAnchorA =  b2Vec2(_pBody->GetLocalCenter().x, _pBody->GetLocalCenter().y - 2); //_pBody->GetLocalCenter() ;
	_chainJointDef.localAnchorB = _pJointBody->GetLocalCenter();

	_ballJointDef.bodyA = _pBody;
	_ballJointDef.bodyB = spikeBall.GetPhysicsBody(); 
	_ballJointDef.localAnchorA = b2Vec2( _pBody->GetLocalCenter().x,_pBody->GetLocalCenter().y + 2);// - (_sprite.getTexture()->getSize().y/2)); //_pBody->GetLocalCenter() ;
	_ballJointDef.localAnchorB = spikeBall.GetPhysicsBody()->GetLocalCenter();

	_pChainJoint = (b2RevoluteJoint *)world.CreateJoint(&_chainJointDef);

	_pBallJoint = (b2RevoluteJoint *)world.CreateJoint(&_ballJointDef);
}



SwingSpikeBall::SwingSpikeBall(float w, float h)
{
	cout << "swing paramless" << endl;
}

SwingSpikeBall::SwingSpikeBall(sf::Texture& texture, sf::Texture& ballTexture, float initX, float initY, float rotation)
	: spikeBall(ballTexture, initX, initY )
{
	cout << "swing paramized" << endl;
	
	_chainSprite.setTexture( texture );	
	//_chainSprite.setColor(sf::Color(34, 244, 66));
	_chainSprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_chainSprite.setRotation( rotation );

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 
	_bodyDef.angle = MathHelper::DegreeToRadian( rotation );
	_bodyDef.type = b2_dynamicBody;

	
	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);


	cout << "swing shape (" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 10.f;
	_fixtureDef.friction = 0.8f;
	_fixtureDef.restitution = 0.5f;

	//setup joint body

	_jointBodyDef.type = b2_staticBody;
	_jointBodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) );

	_jointBodyShape.m_radius = MathHelper::ToUnit( 2.f ); // 2px radius
	
	_jointFixtureDef.density = 1.f;
	_jointFixtureDef.shape = &_jointBodyShape;

	//set up joint
	_ballJointDef.enableMotor = !true;
	_ballJointDef.maxMotorTorque = 15;
	_ballJointDef.motorSpeed = MathHelper::DegreeToRadian( 360 );
	_chainJointDef.collideConnected = false;

	_ballJointDef.collideConnected = false;
}


b2Body* SwingSpikeBall::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& SwingSpikeBall::GetSprite()
{
	return _chainSprite;
}


void SwingSpikeBall::Update(sf::Event e, sf::Time dt)
{
	_chainSprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_chainSprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);

	//cout << _pBody->GetPosition().x << "," << _pBody->GetPosition().y << endl;

		if ( e.type == e.KeyPressed)
	{
		if ( e.key.code == Keyboard::F )
			_pBody->ApplyLinearImpulse(b2Vec2(200,0), b2Vec2( _pBody->GetLocalCenter().x,_pBody->GetLocalCenter().y + 2));
		
	}

	spikeBall.Update(e, dt);
}

void SwingSpikeBall::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _chainSprite );
	//window.draw( _jointBodySprite );
	spikeBall.Draw(window,dt);
}


