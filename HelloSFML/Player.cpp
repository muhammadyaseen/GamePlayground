#include "Player.h"
#include <iostream>
#include <map>
#include <string>
#include "Ball.h"

using namespace std;
using namespace sf;

Player::Player() {}

Player::Player(Texture& texture, float initX, float initY)
{
	//_sprite.setTexture(texture);

	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 2.f),
		MathHelper::ToUnit(texture.getSize().y / 2.f)
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.0f;
}

void Player::Create(Texture& texture, float initX, float initY)
{
	//_sprite.setTexture(texture);
	//_sprite.setTextureRect(IntRect(0, 0, texture.getSize().x / 3, texture.getSize().y));

	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 6.5f),
		MathHelper::ToUnit(texture.getSize().y / 2.f)
		);

	_animatedSprite.setOrigin(
		texture.getSize().x / 7,
		texture.getSize().y / 2
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.f;
}

//
//Player::Player(float initX, float initY)
//{
//	//_sprite.setTexture(texture);
//	//_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
//
//	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
//	_bodyDef.type = b2_dynamicBody;
//	_bodyDef.fixedRotation = true;
//	
//	//_bodyShape.m_radius = MathHelper::ToUnit(texture.getSize().x / 2.f);
//	_bodyShape.m_vertexCount = 4;
//
//	std::cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << std::endl;
//
//	_fixtureDef.shape = &_bodyShape;
//	_fixtureDef.density = 1.f;
//	_fixtureDef.friction = 0.9f;
//	_fixtureDef.restitution = 0.5f;
//}
//
void Player::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

void Player::changeSprite(State state)
{
	_sprite.setTexture(_textureBank[state]);

	switch (state)
	{
	case Idle:
		_sprite.setTextureRect(IntRect(
			0,
			0,
			_textureBank[state].getSize().x / 3,
			_textureBank[state].getSize().y));
		break;

	//case Running:
	//	_sprite.setTextureRect(IntRect(
	//		0,
	//		0,
	//		_spriteBank[state].getSize().x / (_spriteNumbers[state]),
	//		_spriteBank[state].getSize().y));
	//	break;

	//case Walking:
	//	_sprite.setTextureRect(IntRect(
	//		0,
	//		0,
	//		_spriteBank[state].getSize().x / (_spriteNumbers[state] + 1.2),
	//		_spriteBank[state].getSize().y));
	//	break;

	//case Jumping:
	//	_sprite.setTextureRect(IntRect(
	//		0,
	//		0,
	//		_spriteBank[state].getSize().x / (_spriteNumbers[state] + 1.2),
	//		_spriteBank[state].getSize().y));
	//	break;

	default:
		break;
	}
}

void Player::LoadContent()
{
	Texture texture;
	
	// Idle Animation
	texture.loadFromFile("Art\\Edward Elric\\Idle.png");
	_textureBank.insert(pair<State, Texture>(Idle, texture));
	
	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Idle].addFrame(IntRect(  0,  0,  31, 53));
	_animationBank[Idle].addFrame(IntRect( 41,  0,  30, 53));
	_animationBank[Idle].addFrame(IntRect( 85,  0,  30, 53));
	_animationBank[Idle].addFrame(IntRect( 41,  0,  30, 53));
	
	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.25f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	//_spriteBank.insert(pair<State, Texture>(Idle, EdSprite));

	//EdSprite.loadFromFile("Art\\Edward Elric\\Walk.png");
	//_spriteBank.insert(pair<State, Texture>(Walking, EdSprite));

	//EdSprite.loadFromFile("Art\\Edward Elric\\Jump.png");
	//_spriteBank.insert(pair<State, Texture>(Jumping, EdSprite));

	//EdSprite.loadFromFile("Art\\Edward Elric\\Run.png");
	//_spriteBank.insert(pair<State, Texture>(Running, EdSprite));

	// TODO: Set up the Draw Rectangle
	Create(_textureBank[Idle], 100, 100);
	//changeSprite(Idle);
}

void Player::Update(sf::Event e, sf::Time dt, Time frameTime)
{
	_updateTime += dt;
	
	_animatedSprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	_animatedSprite.update(frameTime);

	/*if (Keyboard::isKeyPressed(Keyboard::M) && _animatedSprite.isPlaying() == false)
	{
		_animatedSprite.play();
	}
	else if (Keyboard::isKeyPressed(Keyboard::M) && _animatedSprite.isPlaying() == true)
	{
		_animatedSprite.pause();
	}
	
	if (_updateTime.asSeconds() > 1.f)
	{
		_animatedSprite.update(_animatedSprite.getFrameTime());
	}*/
	
}

void Player::Draw(sf::RenderWindow& window, sf::Time dt)
{
	window.draw(_animatedSprite);
	//window.draw(_sprite);
}

Player::State Player::GetState() { return _state; }
b2Body* Player::GetPhysicsBody() { return _pBody; }
bool Player::IsAlive() { return _alive; }