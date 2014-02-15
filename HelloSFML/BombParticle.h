#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"


class BombParticle
{
private:

   b2Body* _pBody;
   b2BodyDef _bodyDef;
   b2CircleShape _bodyShape;
   b2FixtureDef _fixtureDef;
   
   b2World *_gameWorld;

   sf::Sprite _sprite;


public:
 
   BombParticle(sf::Texture& texture, b2Vec2 initPoint, float blastPower, b2Vec2 angle);
   
   BombParticle();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
      
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   void Explode(sf::Texture bombParticleTexture);

   sf::Sprite& GetSprite();

   void BombParticle::CleanUp();

};
