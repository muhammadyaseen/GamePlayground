#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"

class Box
{
private:
   b2Body * _pBody;
   b2BodyDef _bodyDef;
   b2PolygonShape _bodyShape;
   b2FixtureDef _fixtureDef;
   
   sf::Sprite _sprite;

public:
   //CBox(b2World & world);
   
   Box();

   Box(sf::Texture& texture, float initX, float initY);
   
   void SetWorld(b2World & world);
   
   b2Body* GetBody(); // Get Box2d body

	sf::Sprite& GetSprite();

	void Update(sf::Event e, sf::Time dt); // Get SFML shape

	void Draw( sf::RenderWindow& window, sf::Time dt );
};
