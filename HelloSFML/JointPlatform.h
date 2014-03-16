#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class JointPlatform
{
private:

   b2Body*			_pBody;
   b2BodyDef		_bodyDef;
   b2PolygonShape	_bodyShape;
   b2FixtureDef		_fixtureDef;

   b2JointDef		_jointDef;
   b2BodyDef		_jointBodyDef;
   b2Body*			_pJointBody;
   b2CircleShape	_jointBodyShape;
   b2FixtureDef		_jointFixtureDef;
   b2RevoluteJoint* _pJoint;
   
   sf::Sprite _jointBodySprite;
   sf::Sprite _sprite;

public:

   JointPlatform(float width, float height);
   
   JointPlatform(sf::Texture& texture, float initX, float initY, float rotation = 0);

   JointPlatform();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
      
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   sf::Sprite& GetSprite();


};
