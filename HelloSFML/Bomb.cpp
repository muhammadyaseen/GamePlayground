#include <iostream>
#include "Bomb.h"


using namespace std;

void Bomb::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

Bomb::Bomb()
{
}

Bomb::Bomb(sf::Texture& texture, float initX, float initY, float blastPower)
{
	_timeToClearBombEffect = 0.f;

	_hasExploded = false;

	_blastPower = blastPower;

	_sprite.setTexture( texture );
	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 

	_bodyDef.type = b2_dynamicBody;
	
	_bodyShape.m_radius = MathHelper::ToUnit( texture.getSize().x / 2.f );

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.5f;

}

b2Body* Bomb::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& Bomb::GetSprite()
{
	return _sprite;
}


void Bomb::Update(sf::Event e, sf::Time dt)
{
	_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);

	if ( _hasExploded )
	{
		for ( int i = 0; i < _bombParticles.size(); ++i)
		{
			_bombParticles[i].Update(e, dt);
		}

		_timeToClearBombEffect += dt.asMilliseconds();
	}

	

	if ( _timeToClearBombEffect >= 1000.f )  //1 sec
	{
		for ( int i = 0; i < _bombParticles.size(); ++i)
		{
			_bombParticles[i].CleanUp();
		}

		_hasExploded = false;

		_bombParticles.clear();

		_timeToClearBombEffect = 0;
	}

	//cout << "( " << MathHelper::ToPixel( _pBody->GetPosition().x ) << " , " <<
	//		MathHelper::ToPixel( _pBody->GetPosition().y ) << " )";
}

void Bomb::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );

	if ( _hasExploded )
	{
		for ( int i = 0; i < _bombParticles.size(); ++i)
		{
			_bombParticles[i].Draw(window, dt);
		}
	}
}

void Bomb::Explode( sf::Texture& bombParticleTexture, b2World& world )
{
	int numOfParticles = 40;

	// create bomb particles
	for (int i = 0; i < numOfParticles; i++) 
	{
		float angle = MathHelper::DegreeToRadian( (i / (float)numOfParticles) * 360 );

		b2Vec2 rayDir( sinf(angle), cosf(angle) );

		BombParticle particle( 
			bombParticleTexture,			// what sprite to use for 'displaying' particles
			_pBody->GetPosition(),			// from where should the particle start moving
			_blastPower,					// how powerful is the bomb
			rayDir							// at what angle should it move				
		);

		particle.SetWorld( world );

		_bombParticles.push_back( particle );
	}

	//Ka-Booooooom!
	_hasExploded = true;
}
