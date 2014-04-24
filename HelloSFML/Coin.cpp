#include "Coin.h"


Coin::Coin() : _coinSprite(), _animSequence()
{
}

void Coin::Create(sf::Texture& coinTexture, float x, float y)
{
	//sprite sheet is 8x8 with 64x64 frames
	//_cointTest.setTexture(coinTexture);
	//_cointTest.setPosition( 40, 70);
	
	_animSequence.setSpriteSheet( coinTexture );

	for ( int col = 0; col < 8; col++ )
	{
		for ( int row = 0; row < 8; row++ )
		{
		
			_animSequence.addFrame(sf::IntRect(row*64, col*64 , 64, 64 ));
			//_animSequence.addFrame(sf::IntRect(64 , 64, 64, 64 ));
		}
	}

	_coinSprite.setOrigin( 32,32);
	_coinSprite.setPosition(x,y);
	_coinSprite.setAnimation( _animSequence );
	_coinSprite.setLooped(true);
	_coinSprite.setFrameTime(sf::seconds(0.02));
	_coinSprite.play(_animSequence);

}

void Coin::Update(sf::Event e, sf::Time dt) 
{
	_coinSprite.update(dt);
}

void Coin::Draw( sf::RenderWindow& window, sf::Time dt )
{
	window.draw(_coinSprite );
	//window.draw( _cointTest );
}
Coin::~Coin(void)
{
}
