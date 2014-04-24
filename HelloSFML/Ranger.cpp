#include "Ranger.h"
using namespace sf;
using namespace std;

void Ranger::changeSprite(State _state)
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

	case Attack:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.15f));
		_currentAnimation = &_animationBank[Attack];
		break;
	
	case Hurt:
		_animatedSprite.setLooped(false);
		_animatedSprite.setFrameTime(sf::seconds(0.12f));
		_currentAnimation = &_animationBank[Hurt];
		break;

	default:
		break;
	}

	_animatedSprite.play();

}

void Ranger::LoadContent(int x,int y)
{
	_health = *(new Health(50));
	_knifeExists = false;
	_knifeThrown = false;
	_attackCalled = false;

	_knifeText.loadFromFile("Art\\Ranger\\Knife.png");
	
	Texture texture;

	// Idle Animation
	texture.loadFromFile("Art\\Ranger\\Idle.png");
	_textureBank.insert(pair<State, Texture>(Idle, texture));

	_animationBank[Idle].setSpriteSheet(_textureBank[Idle]);
	_animationBank[Idle].addFrame(IntRect(0, 0, 27 - 0, 67));
	_animationBank[Idle].addFrame(IntRect(51, 0, 78 - 51, 67));
	_animationBank[Idle].addFrame(IntRect(97, 0, 124 - 97, 67));
	_animationBank[Idle].addFrame(IntRect(51, 0, 78 - 51, 67));

	// Walking Animation
	texture.loadFromFile("Art\\Ranger\\Walk.png");
	_textureBank.insert(pair<State, Texture>(Walking, texture));

	_animationBank[Walking].setSpriteSheet(_textureBank[Walking]);
	_animationBank[Walking].addFrame(IntRect(0, 0, 30 - 0, 67));
	_animationBank[Walking].addFrame(IntRect(47, 0, 72 - 47, 67));
	_animationBank[Walking].addFrame(IntRect(92, 0, 116 - 92, 67));
	_animationBank[Walking].addFrame(IntRect(129, 0, 160 - 129, 67));
	_animationBank[Walking].addFrame(IntRect(169, 0, 194 - 169, 67));
	_animationBank[Walking].addFrame(IntRect(205, 0, 231 - 205, 67));

	// Running Animation
	texture.loadFromFile("Art\\Ranger\\Run.png");
	_textureBank.insert(pair<State, Texture>(Running, texture));

	_animationBank[Running].setSpriteSheet(_textureBank[Running]);
	_animationBank[Running].addFrame(IntRect(0,   -5, 52 - 0, 67));
	_animationBank[Running].addFrame(IntRect(66,  -5, 118 - 66, 67));
	_animationBank[Running].addFrame(IntRect(134, -5, 179 - 134, 67));
	_animationBank[Running].addFrame(IntRect(195, -5, 250 - 195, 67));
	_animationBank[Running].addFrame(IntRect(262, -5, 316 - 262, 67));
	_animationBank[Running].addFrame(IntRect(330, -5, 368 - 330, 67));

	// TODO: Jumping Animation
	texture.loadFromFile("Art\\Ranger\\Jump.png");
	_textureBank.insert(pair<State, Texture>(Rising, texture));

	_animationBank[Rising].setSpriteSheet(_textureBank[Rising]);
	_animationBank[Falling].setSpriteSheet(_textureBank[Rising]);
	_animationBank[Landing].setSpriteSheet(_textureBank[Rising]);

	// Correct
	_animationBank[Rising].addFrame(IntRect(188, 13, 234 - 188, 81 - 13));
	_animationBank[Rising].addFrame(IntRect(256, 0, 303 - 256, 70 - 0));

	// Correct
	_animationBank[Falling].addFrame(IntRect(330, 21, 382 - 330, 91 - 21));

	// TODO: Correct it
	_animationBank[Landing].addFrame(IntRect(171, 1, 210 - 171, 58 - 1));
	_animationBank[Landing].addFrame(IntRect(222, 9, 264 - 222, 65 - 9));
	_animationBank[Landing].addFrame(IntRect(274, 15, 316 - 274, 65 - 15));
	_animationBank[Landing].addFrame(IntRect(330, 15, 380 - 330, 65 - 15));

	// Attack Animation
	texture.loadFromFile("Art\\Ranger\\Attack.png");
	_textureBank.insert(pair<State, Texture>(Attack, texture));

	_animationBank[Attack].setSpriteSheet(_textureBank[Attack]);
	_animationBank[Attack].addFrame(IntRect(0,   0, 27 - 0,    70));
	_animationBank[Attack].addFrame(IntRect(48,  0, 94 - 48,   70));
	_animationBank[Attack].addFrame(IntRect(104, 0, 131 - 104, 70));
	_animationBank[Attack].addFrame(IntRect(153, 0, 178 - 153, 70));
	_animationBank[Attack].addFrame(IntRect(193, 0, 242 - 193, 70));
	_animationBank[Attack].addFrame(IntRect(265, 0, 312 - 265, 70));
	_animationBank[Attack].addFrame(IntRect(329, 0, 376 - 329, 70));
	_animationBank[Attack].addFrame(IntRect(390, 0, 437 - 390, 70));
	_animationBank[Attack].addFrame(IntRect(443, 0, 479 - 443, 70));

	// Hurt Animation
	texture.loadFromFile("Art\\Ranger\\Hurt.png");
	_textureBank.insert(pair<State, Texture>(Hurt, texture));

	_animationBank[Hurt].setSpriteSheet(_textureBank[Hurt]);
	_animationBank[Hurt].addFrame(IntRect(  0, -5,  47 -   0, 67));
	_animationBank[Hurt].addFrame(IntRect( 67, -5, 118 -  67, 67));
	_animationBank[Hurt].addFrame(IntRect(140, -5, 191 - 140, 67));
	_animationBank[Hurt].addFrame(IntRect(598, -5, 640 - 598, 67));

	// Setting up the animated sprite
	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	create(_textureBank[Idle],x, y);
}

void Ranger::create(Texture& texture, float initX, float initY)
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
		texture.getSize().y / 2
		);

	cout << "(" << _bodyDef.position.x << "," << _bodyDef.position.y << ")" << endl;

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.restitution = 0.3f;
}

void Ranger::handleState()
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
	if (_attackCalled && !_knifeExists)
	{
		_state = Attack;
		_attackCalled = false;
	}
	else if (_state == Attack && _animatedSprite.getCurrentFrame() == 4 && !_knifeExists)
	{
		_knifeThrown = true;
		_knifeExists = true;
	}
	else if (_state == Attack && !_animatedSprite.isPlaying())
	{
		_state = Idle;
	}

	// Only allow normal movement if character is not recoiling from damage
	// or dying or attacking
	if (_state != Hurt && _state != Dead && _state != Attack)
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

		// Judge whether the character is in air or not
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

void Ranger::handleEvent(Event gameEvent, Player& player)
{
	b2Vec2 position = _pBody->GetPosition();
	b2Vec2 playerPosition = player.GetPhysicsBody()->GetPosition();

	float distanceFromPlayer = distanceFromBody(player.GetPhysicsBody());
	
	if (distanceFromPlayer < 3.6)
	{
		playerFound = true;
	}
	else
	{
		playerFound = false;
	}
	
	if (playerFound && !_inAir)
	{
		if ((playerPosition.x - position.x) > 0)
			playerOnRight = 1;
		else playerOnRight = -1;
	
		if (distanceFromPlayer > 2.4)
		{
			_pBody->SetLinearVelocity( b2Vec2( 
				1.2 * playerOnRight, 
				_pBody->GetLinearVelocity().y
				) );
		}
		// Judge whether to attack or not with a chance of 1/60
		else if (distanceFromPlayer > 2)
		{
			int choice = rand() % 2;

			if (choice == 0)
			{
				_attackCalled = true;
			}
		}
	}
}

void Ranger::Update(Event gameEvent, Player& player, Time dt, Time frameTime)
{
	if (_state != Hurt) handleEvent(gameEvent, player);
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

	if (_knifeThrown)
	{
		_pKnife = new Projectile(_knifeText,
			_animatedSprite.getPosition().x,
			_animatedSprite.getPosition().y,
			_animatedSprite.getScale().x);

		_pKnife->IamA( KNIFE )->ICollideWith( EDWARD );

		_pKnife->SetWorld( *(_pBody->GetWorld()) );
		_knifeThrown = false;
	}

	if (_knifeExists && _pKnife->Update(gameEvent, dt))
	{
		//_pBody->GetWorld()->DestroyBody(_knife.GetPhysicsBody());
		delete _pKnife;
		_knifeExists = false;
	}
}

void Ranger::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
	if (_knifeExists) { _pKnife->Draw(window, dt); }
}

Ranger::Ranger() {}
b2Body* Ranger::GetPhysicsBody() { return _pBody; }