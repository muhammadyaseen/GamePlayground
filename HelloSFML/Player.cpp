#include "Player.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace sf;

Player::Player() {}

Player::Player(Texture& texture, float initX, float initY)
{
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
	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 6.5f),
		MathHelper::ToUnit(texture.getSize().y / 2.f)
		);

	_animatedSprite.setOrigin(
		texture.getSize().x / 7,
		(texture.getSize().y / 2) - 4
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
	_pBody->SetUserData( this );
}

void Player::changeSprite(State _state)
{
	switch (_state)
	{
	case Idle:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Idle];
		
		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 3
			);

		break;

	case Walking:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Walking];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 4
			);
		break;

	case Running:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Running];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 4
			);
		break;

	case Rising:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.1f));
		_currentAnimation = &_animationBank[Rising];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			_textureBank[Idle].getSize().y / 2
			);
		break;

	case Falling:
		_animatedSprite.setLooped(true);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Falling];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			_textureBank[Idle].getSize().y / 2
			);
		break;

	case Landing:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
		_currentAnimation = &_animationBank[Landing];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 4
			);
		break;
	
	case Hurt:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.15f));
		_currentAnimation = &_animationBank[Hurt];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 8
			);
		break;

	case Attack1:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.15f));
		_currentAnimation = &_animationBank[Attack1];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 3
			);
		break;

	case Attack2:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.15f));
		_currentAnimation = &_animationBank[Attack2];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 3
			);
		break;

	case Attack3:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.13f));
		_currentAnimation = &_animationBank[Attack3];

		_animatedSprite.setOrigin(
			_textureBank[Idle].getSize().x / 7,
			(_textureBank[Idle].getSize().y / 2) - 3
			);
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
	
	if (_hit) 
	{
		_state = Hurt;
		_hit = false;
	}

	// If the Hurt animation is done, then make the character Idle again
	if (_state == Hurt && !_animatedSprite.isPlaying())
	{
		_state = Idle;
	}

	// Attacking logic
	if (_attack1Called)
	{
		_state = Attack1;
		_attack1Called = false;
	}
	
	if (_state == Attack1 && !_animatedSprite.isPlaying())
	{
		if (_attack2Called)
		{
			_state = Attack2;
			_attack2Called = false;
		}
		else _state = Idle;
	}
	else if (_state == Attack2 && !_animatedSprite.isPlaying())
	{
		if (_attack3Called) 
		{
			_state = Attack3;
			_attack3Called = false;
		}
		else _state = Idle;
	}
	else if (_state == Attack3 && !_animatedSprite.isPlaying())
	{
		_state = Idle;
	}
	
	// Set the busy variable so if statements are easier to handle
	bool _busy = _state == Hurt || _state == Dead || _state == Attack1 || _state == Attack2 || _state == Attack3 || _state == Special;

	// Only allow normal movement if character is not recoiling from damage
	// or dying or attacking
	if (!_busy)
	{
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
	}
	// If movement is in neither of the dimensions and the player is just standing
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
					_pBody->ApplyLinearImpulse(b2Vec2(10, 15), _pBody->GetWorldCenter());
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_pBody->ApplyLinearImpulse(b2Vec2(-10, 15), _pBody->GetWorldCenter());
				}
				else
				{
					_pBody->ApplyLinearImpulse(b2Vec2(0, 15), _pBody->GetWorldCenter());
				}
			}
			
			// Walking and attacking
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
				
				else if (Keyboard::isKeyPressed(Keyboard::A))
				{
					if (_state == Attack2 && _animatedSprite.getCurrentFrame() > 2)
					{
						_attack3Called = true;
					}

					else if (_state == Attack1 && _animatedSprite.getCurrentFrame() > 1)
					{
						_attack2Called = true;
					}

					else if (_state != Attack1 && _state != Attack2 && _state != Attack3)
					{
						_attack1Called = true;
					}
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

void Player::LoadContent(int x,int y)
{
	_health = *(new Health(50));
	_hit = false;
	_attack1Called = false;
	_attack2Called = false;
	_attack3Called = false;

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

	// Hurt Animation
	texture.loadFromFile("Art\\Edward Elric\\Hurt.png");
	_textureBank.insert(pair<State, Texture>(Hurt, texture));

	_animationBank[Hurt].setSpriteSheet(_textureBank[Hurt]);
	_animationBank[Hurt].addFrame(IntRect( 44, 0, 85 - 44,  47));
	_animationBank[Hurt].addFrame(IntRect( 91, 0, 124 - 91, 47));
	_animationBank[Hurt].addFrame(IntRect( 0,  0, 40 - 0,   47));

	// Attack1 Animation
	texture.loadFromFile("Art\\Edward Elric\\Attack1.png");
	_textureBank.insert(pair<State, Texture>(Attack1, texture));

	_animationBank[Attack1].setSpriteSheet(_textureBank[Attack1]);
	_animationBank[Attack1].addFrame(IntRect(0,  0,  31 -   0, 54));
	_animationBank[Attack1].addFrame(IntRect(38, 0,  81 -  38, 54));
	_animationBank[Attack1].addFrame(IntRect(89, 0, 131 -  89, 54));
	_animationBank[Attack1].addFrame(IntRect(142,0, 180 - 142, 54));

	// Attack2 Animation
	texture.loadFromFile("Art\\Edward Elric\\Attack2.png");
	_textureBank.insert(pair<State, Texture>(Attack2, texture));

	_animationBank[Attack2].setSpriteSheet(_textureBank[Attack2]);
	_animationBank[Attack2].addFrame(IntRect(  0, 0,  33 -   0, 53));
	_animationBank[Attack2].addFrame(IntRect( 46, 0,  74 -  46, 53));
	_animationBank[Attack2].addFrame(IntRect(147, 0, 203 - 147, 53));
	_animationBank[Attack2].addFrame(IntRect(213, 0, 264 - 213, 53));
	_animationBank[Attack2].addFrame(IntRect(272, 0, 301 - 272, 53));
	_animationBank[Attack2].addFrame(IntRect(309, 0, 344 - 309, 53));
	_animationBank[Attack2].addFrame(IntRect(354, 0, 384 - 354, 53));

	// Attack3 Animation
	texture.loadFromFile("Art\\Edward Elric\\Attack3.png");
	_textureBank.insert(pair<State, Texture>(Attack3, texture));

	_animationBank[Attack3].setSpriteSheet(_textureBank[Attack3]);
	_animationBank[Attack3].addFrame(IntRect(  0, 0,  32 -   0, 54));
	_animationBank[Attack3].addFrame(IntRect( 42, 0,  80 -  42, 54));
	_animationBank[Attack3].addFrame(IntRect( 88, 0, 123 -  88, 54));
	_animationBank[Attack3].addFrame(IntRect(128, 0, 197 - 128, 54));
	_animationBank[Attack3].addFrame(IntRect(206, 0, 263 - 206, 54));
	_animationBank[Attack3].addFrame(IntRect(273, 0, 327 - 273, 54));
	_animationBank[Attack3].addFrame(IntRect(334, 0, 387 - 334, 54));
	_animationBank[Attack3].addFrame(IntRect(397, 0, 433 - 397, 54));
	_animationBank[Attack3].addFrame(IntRect(443, 0, 473 - 443, 54));
	_animationBank[Attack3].addFrame(IntRect(483, 0, 516 - 483, 54));


	//// Code for the armblade attack
	//_animationBank[Attack3].setSpriteSheet(_textureBank[Attack3]);
	//_animationBank[Attack3].addFrame(IntRect(  0, 0,  32 -   0, 57));
	//_animationBank[Attack3].addFrame(IntRect( 40, 0,  78 -  40, 57));
	//_animationBank[Attack3].addFrame(IntRect( 83, 0, 119 -  83, 57));
	//_animationBank[Attack3].addFrame(IntRect(129, 0, 161 - 129, 57));
	//_animationBank[Attack3].addFrame(IntRect(170, 0, 203 - 173, 57));
	//_animationBank[Attack3].addFrame(IntRect(211, 0, 248 - 211, 57));
	//_animationBank[Attack3].addFrame(IntRect(259, 0, 295 - 259, 57));
	//_animationBank[Attack3].addFrame(IntRect(306, 0, 344 - 306, 57));
	//_animationBank[Attack3].addFrame(IntRect(352, 0, 434 - 352, 57));
	//_animationBank[Attack3].addFrame(IntRect(447, 0, 505 - 447, 57));
	//_animationBank[Attack3].addFrame(IntRect(513, 0, 551 - 513, 57));
	//_animationBank[Attack3].addFrame(IntRect(561, 0, 599 - 561, 57));
	//_animationBank[Attack3].addFrame(IntRect(609, 0, 642 - 609, 57));
	//_animationBank[Attack3].addFrame(IntRect(651, 0, 689 - 651, 57));
	//_animationBank[Attack3].addFrame(IntRect(697, 0, 731 - 697, 57));


	// Setting up the animated sprite
	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	create(_textureBank[Idle], x, y);
}

void Player::Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime)
{
	if (_state != Hurt && _state != Dead) handleEvent(gameEvent, oldGameEvent);
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
	if (_state != Hurt)
	{
		_health -= amount;
		
		if (_health == 0)
		{
			_alive = false;
		}
		else _hit = true;
	}
}

Player::State Player::GetState() { return _state; }
b2Body* Player::GetPhysicsBody() { return _pBody; }
bool Player::IsAlive() { return _alive; }

void Player::Respawn(b2World *world,int x,int y)
{
	world->DestroyBody(_pBody);
	create(_textureBank[Idle],x,y);
	SetWorld(*world);

}