#include "StaticPlatform.h"
#include <iostream>

using namespace std;

StaticPlatform::StaticPlatform(void)
{
}



void StaticPlatform::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

//when we have to fill a region of known width with a sprite , we use this ctor
StaticPlatform::StaticPlatform(sf::Texture& texture, float initX, float initY, float width, float rotation)
{
	_sprite.setTexture( texture );

	//texture will be repeated to fill the given 'width'

	_sprite.setTextureRect( IntRect( 0, 0, width, texture.getSize().y ) ) ;

	texture.setRepeated( true );
	
	_sprite.setOrigin( (width/2.f), (texture.getSize().y/2.f));

	_bodyDef.position.Set( MathHelper::ToUnit( initX  ), MathHelper::ToUnit( initY ) ); 

	_bodyDef.angle = MathHelper::DegreeToRadian( rotation );

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( width / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 0;//1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;

	
}



StaticPlatform::StaticPlatform(sf::Texture& texture, float initX, float initY, int repeatTimes, float restitution)
{
	_sprite.setTexture( texture );

	//texture will be repeated 'repeatTimes' times along X-direction
	_sprite.setTextureRect( IntRect( 0, 0, repeatTimes * texture.getSize().x, texture.getSize().y ) ) ;

	texture.setRepeated( true );
	
	_sprite.setOrigin( repeatTimes * texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 

	//_bodyDef.angle = MathHelper::DegreeToRadian( rotation );

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( repeatTimes * texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = restitution;

}


StaticPlatform::StaticPlatform(sf::Texture& texture, float initX, float initY, float rotation)
{
	_sprite.setTexture( texture );
	
	_sprite.setOrigin( texture.getSize().x / 2.f, texture.getSize().y / 2.f);

	_sprite.setRotation( rotation );

	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 

	_bodyDef.angle = MathHelper::DegreeToRadian( rotation );

	_bodyDef.type = b2_staticBody;

	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;
	
	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;

}


b2Body* StaticPlatform::GetPhysicsBody()
{
	return _pBody;
}

sf::Sprite& StaticPlatform::GetSprite()
{
	return _sprite;
}


void StaticPlatform::Update(sf::Event e, sf::Time dt)
{
	//_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);
}

void StaticPlatform::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}


