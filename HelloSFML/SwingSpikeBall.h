#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"
#include "SpikeBall.h"

class SwingSpikeBall
{
private:

	//consists of 2 joints, a chain (body + sprite), a spike ball (body + sprite)

	Ball spikeBall;

	b2Body*				_pBody;			//body associateed with chain
	b2BodyDef			_bodyDef;
	b2PolygonShape		_bodyShape;		//shape associated with the chain
	b2FixtureDef		_fixtureDef;
	
	b2RevoluteJointDef	_chainJointDef; //joins the chain with (imaginary) wall / support.
	b2BodyDef			_jointBodyDef;	//body def for the join that joins chain with (imaginary) wall
	b2Body*				_pJointBody;  
	b2CircleShape		_jointBodyShape;
	b2FixtureDef		_jointFixtureDef;

	b2RevoluteJoint*	_pChainJoint;	//joins chain and wall
	
	b2RevoluteJointDef	_ballJointDef;
	b2RevoluteJoint*	_pBallJoint;	//joins the spikey ball with chain

	sf::Sprite _chainSprite; //sprite for the chain

public:

   SwingSpikeBall(float width, float height);
   
   SwingSpikeBall(sf::Texture& texture, sf::Texture& jointTexture, float initX, float initY, float rotation = 0);

   SwingSpikeBall();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
	  
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   sf::Sprite& GetSprite();

   
   SwingSpikeBall* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; spikeBall.IamA( category ); return this; } 

   void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; spikeBall.ICollideWith( collisionPartners ); }


};

