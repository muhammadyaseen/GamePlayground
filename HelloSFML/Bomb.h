#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"
#include "BombParticle.h"
#include <vector>

class Bomb
{
private:

   b2Body* _pBody;
   b2BodyDef _bodyDef;
   b2CircleShape _bodyShape;
   b2FixtureDef _fixtureDef;
   
   sf::Sprite _sprite;
   std::vector<BombParticle> _bombParticles;
   float _blastPower;
   bool _hasExploded;

   // Our game clock is restarted after 16 milli-sec
   // we 'accumulate' the elapsed time in this attribute

   float _timeToClearBombEffect;

public:
 
   Bomb(sf::Texture& texture, float initX, float initY, float blastPower);
   
   Bomb();
   
   void SetWorld(b2World& world);
   
   b2Body* GetPhysicsBody(); 
      
   void Update(sf::Event e, sf::Time dt);

   void Draw( sf::RenderWindow& window, sf::Time dt );

   void Explode(sf::Texture& bombParticleTexture, b2World& world);

   sf::Sprite& GetSprite();

};
