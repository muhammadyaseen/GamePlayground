#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class StaticPlatform
{
private:

   b2Body* _pBody;
   b2BodyDef _bodyDef;
   b2PolygonShape _bodyShape;
   b2FixtureDef _fixtureDef;
   
   sf::Sprite _sprite;



public:

   /*StaticPlatform(float width, float height);*/

   StaticPlatform(sf::Texture& texture, float initX, float initY, float width, float rotation = 0);

   StaticPlatform(sf::Texture& texture, float initX, float initY, float rotation = 0);

   StaticPlatform(sf::Texture& texture, float initX, float initY, int repeatTimes,float restitution=0.3);

   StaticPlatform();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
	  
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   sf::Sprite& GetSprite();
	
   StaticPlatform* IamA( uint16 category ) { _fixtureDef.filter.categoryBits = category; return this; } 

	void ICollideWith( uint16 collisionPartners ) {  _fixtureDef.filter.maskBits = collisionPartners; }

};

