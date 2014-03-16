#pragma once
#include "Ball.h"

class Wheel :	public Ball
{

private:

   b2RevoluteJointDef		_jointDef;
   b2BodyDef				_jointBodyDef;
   b2Body*					_pJointBody;
   b2CircleShape			_jointBodyShape;
   b2FixtureDef				_jointFixtureDef;
   b2RevoluteJoint*			_pJoint;
   
public:
	Wheel();

	Wheel(sf::Texture& texture, float initX, float initY);
   
	void SetWorld(b2World& world);
   
	b2Body* GetPhysicsBody(); 
	  
	void Update(sf::Event e, sf::Time dt);

	void Draw( sf::RenderWindow& window, sf::Time dt );

	sf::Sprite& GetSprite();
};

