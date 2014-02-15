//box.cpp file
#include "box.h"
#include <iostream>

using namespace std;


void Box::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

Box::Box()
{
}

Box::Box( sf::Texture& texture , float initX, float initY)
{
	_sprite.setTexture( texture );

	_sprite.setOrigin( texture.getSize().x / 2, texture.getSize().y / 2 );
	
	_bodyDef.position.Set( MathHelper::ToUnit( initX ), MathHelper::ToUnit( initY ) ); 
	
	_bodyDef.type = b2_dynamicBody;
	
	_bodyShape.SetAsBox( 
		MathHelper::ToUnit( texture.getSize().x / 2.f ),
		MathHelper::ToUnit( texture.getSize().y / 2.f )
	);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;

}



b2Body* Box::GetBody()
{
	return _pBody;
}

sf::Sprite& Box::GetSprite() 
{
	return _sprite;
}

void Box::Update(sf::Event e, sf::Time dt)
{
	_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_sprite.setPosition(
			MathHelper::ToPixel( _pBody->GetPosition().x ) ,
			MathHelper::ToPixel( _pBody->GetPosition().y ) 
		);

		//cout << "( " << MathHelper::ToPixel( _pBody->GetPosition().x ) << " , " <<
		//	MathHelper::ToPixel( _pBody->GetPosition().y ) << " )";
}

void Box::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw( _sprite );
}
