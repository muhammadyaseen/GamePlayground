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

	default:
		break;
	}

	_animatedSprite.play();

}

void Ranger::LoadContent()
{
	_health = *(new Health(50));

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

	// TODO: Running Animation
	texture.loadFromFile("Art\\Ranger\\Run.png");
	_textureBank.insert(pair<State, Texture>(Running, texture));

	_animationBank[Running].setSpriteSheet(_textureBank[Running]);
	_animationBank[Running].addFrame(IntRect(0, 0, 42 - 0, 51));
	_animationBank[Running].addFrame(IntRect(47, 0, 96 - 47, 51));
	_animationBank[Running].addFrame(IntRect(106, 0, 160 - 106, 51));
	_animationBank[Running].addFrame(IntRect(174, 0, 214 - 174, 51));
	_animationBank[Running].addFrame(IntRect(221, 0, 277 - 221, 51));
	_animationBank[Running].addFrame(IntRect(285, 0, 337 - 285, 51));

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

	// Setting up the animated sprite
	_animatedSprite.setLooped(true);
	_animatedSprite.play();
	_animatedSprite.setFrameTime(sf::seconds(0.2f));

	_currentAnimation = &_animationBank[Idle];

	_animatedSprite.setAnimation(*_currentAnimation);

	create(_textureBank[Idle], 500, 500);
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

void Ranger::handleEvent(Event gameEvent, Player& player)
{
	b2Vec2 position = _pBody->GetPosition();
	b2Vec2 playerPosition = player.GetPhysicsBody()->GetPosition();

	float distanceFromPlayer = distanceFromBody(player.GetPhysicsBody());
	
	if (distanceFromPlayer < 3)
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
	
		if (distanceFromPlayer > 1.2)
		{
			_pBody->SetLinearVelocity( b2Vec2( 
				1.2 * playerOnRight, 
				_pBody->GetLinearVelocity().y
				) );
		}
	}
}

void Ranger::Update(Event gameEvent, Player& player, Time dt, Time frameTime)
{
	//_animatedSprite.setAnimation(*_currentAnimation);
	handleEvent(gameEvent, player);
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

Ranger::Ranger()
{

}

b2Body* Ranger::GetPhysicsBody() { return _pBody; }