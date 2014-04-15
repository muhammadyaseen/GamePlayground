#include "Player.h"
#include <iostream>
#include <map>
#include <string>
//#include "Ball.h"

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

void Player::create(Texture& texture, float initX, float initY)
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
	_fixtureDef.restitution = 0.3f;
}

void Player::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

void Player::changeSprite(State _state)
{
	switch (_state)
	{
	case Idle:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Idle];
		break;

	case Walking:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Walking];
		break;

	case Running:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Running];
		break;

	case Rising:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.1f));
		_currentAnimation = &_animationBank[Rising];
		break;

	case Falling:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Falling];
		break;

	case Landing:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Landing];
		break;

	default:
		break;
	}

	_animatedSprite.play();

}

void Player::handleState()
{
	// Remember what the player's _state was in the previous update
	_previousState = _state;

	// Change the current _state according to vertical events
	if (_pBody->GetLinearVelocity().y > 0.1)
	{
		_state = Falling;
	}
	else if (_pBody->GetLinearVelocity().y == 0)
	{
		_state = Idle;
	}
	else if (_pBody->GetLinearVelocity().y < -0.1)
	{
		_state = Rising;
	}

	// Judge whether the player is in air or not
	if (_state != Rising && _state != Falling) _inAir = false;
	else _inAir = true;

	// Change the current _state according to horizontal events
	if (!_inAir)
	{
		if (_pBody->GetLinearVelocity().x < -1.5)
		{
			_state = Running;
		}
		else if (_pBody->GetLinearVelocity().x < 0)
		{
			_state = Walking;
		}
		else if (_pBody->GetLinearVelocity().x > 0)
		{
			_state = Walking;
		}
		if (_pBody->GetLinearVelocity().x > 1.5)
		{
			_state = Running;
		}

		if (_pBody->GetLinearVelocity().x < -0.1) _movingForward = false;
		else if (_pBody->GetLinearVelocity().x > 0.1) _movingForward = true;
	}

	// If movement is in neither of the dimensions and the player is just standing

	// TODO: Hurt animation
}

void Player::handleEvent(Event gameEvent, Event oldGameEvent)
{

#pragma region CommentedCode
	// Events that you don't want to be perpetual (eg. initiating a jump)
	//if (gameEvent.type == Event::KeyPressed)
	//{
	//	// Making sure the player is in a position to take action
	//	if (!_inAir)
	//	{
	//		// Initializing a jump based on keys pressed
	//		if (gameEvent.key.code == Keyboard::Up)
	//		{
	//			// Right jump
	//			if (Keyboard::isKeyPressed(Keyboard::Right))
	//			{
	//				_pBody->ApplyLinearImpulse(b2Vec2(2, 10), _pBody->GetWorldCenter());
	//			}
	//			// Left jump
	//			else if (Keyboard::isKeyPressed(Keyboard::Right))
	//			{
	//				_pBody->ApplyLinearImpulse(b2Vec2(-2, 10), _pBody->GetWorldCenter());
	//			}
	//			// Jump up
	//			else
	//			{
	//				_pBody->ApplyLinearImpulse(b2Vec2(0, 10), _pBody->GetWorldCenter());
	//			}
	//		}
	//	}
	//	// If the player is performing a jump, the light movements
	//	else
	//	{
	//		if (Keyboard::isKeyPressed(Keyboard::Right))
	//		{
	//			_pBody->ApplyForceToCenter(b2Vec2( 1, 0));
	//		}

	//		if (Keyboard::isKeyPressed(Keyboard::Left))
	//		{
	//			_pBody->ApplyForceToCenter(b2Vec2(-1, 0));
	//		}
	//	}
	//}
	
	// Leftward or rightward movement
	//if (!_inAir)
	//{
	//	if (Keyboard::isKeyPressed(Keyboard::LShift))
	//	{
	//		if (Keyboard::isKeyPressed(Keyboard::Right))
	//		{
	//			_pBody->SetLinearVelocity(b2Vec2(3, 0));
	//		}

	//		if (Keyboard::isKeyPressed(Keyboard::Left))
	//		{
	//			_pBody->SetLinearVelocity(b2Vec2(-3, 0));
	//		}
	//	}
	//	else
	//	{
	//		if (Keyboard::isKeyPressed(Keyboard::Right))
	//		{
	//			_pBody->SetLinearVelocity(b2Vec2(1.5, _pBody->GetLinearVelocity().y));
	//		}

	//		if (Keyboard::isKeyPressed(Keyboard::Left))
	//		{
	//			_pBody->SetLinearVelocity(b2Vec2(-1.5, _pBody->GetLinearVelocity().y));
	//		}
	//	}
	//}

#pragma endregion

	// When player is grounded
	if (!_inAir)
	{
		// Running and jumping
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					_pBody->ApplyLinearImpulse(b2Vec2( 3, 8), _pBody->GetWorldCenter());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_pBody->ApplyLinearImpulse(b2Vec2(-3, 8), _pBody->GetWorldCenter());
				}
				else
				{
					_pBody->ApplyLinearImpulse(b2Vec2(0, 8), _pBody->GetWorldCenter());
				}
			}
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					_pBody->SetLinearVelocity(b2Vec2( 3, _pBody->GetLinearVelocity().y));
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_pBody->SetLinearVelocity(b2Vec2(-3, _pBody->GetLinearVelocity().y));
				}
			}
		} // End of running and jumping

		// Walking and jumping
		else
		{
			// Jumping
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					_pBody->ApplyLinearImpulse(b2Vec2(10, 8), _pBody->GetWorldCenter());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_pBody->ApplyLinearImpulse(b2Vec2(-10, 8), _pBody->GetWorldCenter());
				}
				else
				{
					_pBody->ApplyLinearImpulse(b2Vec2(0, 8), _pBody->GetWorldCenter());
				}
			}
			
			// Walking
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					_pBody->SetLinearVelocity(b2Vec2( 1.5, _pBody->GetLinearVelocity().y));
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_pBody->SetLinearVelocity(b2Vec2(-1.5, _pBody->GetLinearVelocity().y));
				}
			}
		} // End of walking and jumping
	} // End of grounded actions

	// Actions to do in air
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				_pBody->SetLinearVelocity(b2Vec2( 3, _pBody->GetLinearVelocity().y));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				_pBody->SetLinearVelocity(b2Vec2(-3, _pBody->GetLinearVelocity().y));
			}
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				_pBody->SetLinearVelocity(b2Vec2( 1.5, _pBody->GetLinearVelocity().y));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				_pBody->SetLinearVelocity(b2Vec2(-1.5, _pBody->GetLinearVelocity().y));
			}
		}
	} // End of air actions
	
}

void Player::LoadContent()
{
	_health = Health(50);
	
	Texture texture;
	
	// Idle Animation
	texture.loadFromFile("Art\\Edward Elric\\Idle.png");
	_textureBank.insert(pair<State, Texture>(Idle, texture));
	
	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Idle].addFrame(IntRect(  0,  0,  31 -  0, 53 ));
	_animationBank[Idle].addFrame(IntRect( 41,  0,  71 - 41, 53 ));
	_animationBank[Idle].addFrame(IntRect( 85,  0, 115 - 85, 53 ));
	_animationBank[Idle].addFrame(IntRect( 41,  0,  71 - 41, 53 ));
	
	// Walking Animation
	texture.loadFromFile("Art\\Edward Elric\\Walk.png");
	_textureBank.insert(pair<State, Texture>(Walking, texture));

	_animationBank[Walking].setSpriteSheet(_textureBank[Walking]);
	_animationBank[Walking].addFrame(IntRect(   0,  0,  22 -   0, 51 ));
	_animationBank[Walking].addFrame(IntRect(  35,  0,  60 -  35, 51 ));
	_animationBank[Walking].addFrame(IntRect(  72,  0, 100 -  72, 51 ));
	_animationBank[Walking].addFrame(IntRect( 108,  0, 129 - 108, 51 ));
	_animationBank[Walking].addFrame(IntRect( 143,  0, 166 - 143, 51 ));
	_animationBank[Walking].addFrame(IntRect( 179,  0, 207 - 179, 51 ));

	// Running Animation
	texture.loadFromFile("Art\\Edward Elric\\Run.png");
	_textureBank.insert(pair<State, Texture>(Running, texture));

	_animationBank[Running].setSpriteSheet(_textureBank[Running]);
	_animationBank[Running].addFrame(IntRect(   0,  0,  42 -   0, 51 ));
	_animationBank[Running].addFrame(IntRect(  47,  0,  96 -  47, 51 ));
	_animationBank[Running].addFrame(IntRect( 106,  0, 160 - 106, 51 ));
	_animationBank[Running].addFrame(IntRect( 174,  0, 214 - 174, 51 ));
	_animationBank[Running].addFrame(IntRect( 221,  0, 277 - 221, 51 ));
	_animationBank[Running].addFrame(IntRect( 285,  0, 337 - 285, 51 ));

	// Jumping Animation
	texture.loadFromFile("Art\\Edward Elric\\Jump.png");
	_textureBank.insert(pair<State, Texture>(Rising, texture));

	_animationBank[Rising].setSpriteSheet(_textureBank[Rising]);
	_animationBank[Falling].setSpriteSheet(_textureBank[Rising]);
	_animationBank[Landing].setSpriteSheet(_textureBank[Rising]);

	_animationBank[Rising].addFrame(IntRect(   0, 15,  36 -   0, 66 - 15));
	_animationBank[Rising].addFrame(IntRect(  39,  2,  76 -  39, 65 -  2));
	_animationBank[Rising].addFrame(IntRect(  85,  2, 120 -  85, 65 -  2));

	_animationBank[Falling].addFrame(IntRect( 124,  0, 168 - 124, 57 -  0));

	_animationBank[Landing].addFrame(IntRect( 171,  1, 210 - 171, 58 -  1));
	_animationBank[Landing].addFrame(IntRect( 222,  9, 264 - 222, 65 -  9));
	_animationBank[Landing].addFrame(IntRect( 274, 15, 316 - 274, 65 - 15));
	_animationBank[Landing].addFrame(IntRect( 330, 15, 380 - 330, 65 - 15));

	// Setting up the animated sprite
	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	// Load hurt state

	create(_textureBank[Idle], 200, 500);
}

void Player::Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime)
{
	handleEvent(gameEvent, oldGameEvent);
	handleState();

	if (_state != _previousState)
	{
		changeSprite(_state);
		_animatedSprite.setAnimation(*_currentAnimation);
	}

	_animatedSprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	_animatedSprite.update(frameTime);

	// Scaling is like a multiplication by -1. So it should only
	// be done once. The following code tries to guarantee that.
	if (_movingForward && _animatedSprite.getScale().x < 0)
		_animatedSprite.scale(-1.f, 1.f);
	else if (!_movingForward && _animatedSprite.getScale().x > 0) 
		_animatedSprite.scale(-1.f, 1.f);
	
}


void Player::Damage(int amount)
{
	_health -= amount;
	// TODO: Change state to Hurt
}

Player::State Player::GetState() { return _state; }
b2Body* Player::GetPhysicsBody() { return _pBody; }
bool Player::IsAlive() { return _alive; }