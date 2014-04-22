#include "Projectile.h"

#include "MathHelper.h"

void Projectile::SetWorld(b2World & world)
{
	_pBody = world.CreateBody(&_bodyDef);
	_pBody->CreateFixture(&_fixtureDef);
}

Projectile::Projectile(sf::Texture texture, int initX, int initY, int direction)
{
	_range = 3;
	_direction = direction;
	_initpos = b2Vec2(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	_sprite.setScale(direction, 1);

	_bodyDef.position.Set(MathHelper::ToUnit(initX), MathHelper::ToUnit(initY));
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.fixedRotation = true;
	//_bodyDef.linearDamping = 0;
	//_bodyDef.gravityScale = 0;
	
	//_bodyShape.m_radius = MathHelper::ToUnit(texture.getSize().x / 2.f);

	_bodyShape.SetAsBox(
		MathHelper::ToUnit(texture.getSize().x / 2.f),
		MathHelper::ToUnit(texture.getSize().y / 2.f)
		);

	_fixtureDef.shape = &_bodyShape;
	_fixtureDef.density = 1.f;
	_fixtureDef.friction = 0.5f;
	
	//_sprite.setTexture(texture);
	//_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	

	//_bodyDef.type = b2_dynamicBody;
	//_bodyDef.fixedRotation = true;
	//_bodyDef.linearDamping = 0;
	//_bodyDef.gravityScale = 0;
	//_bodyDef.position = initpos;
	//_bodyDef.linearVelocity = b2Vec2(3 * direction, 0);


	//_bodyShape.m_radius = MathHelper::ToUnit(texture.getSize().x / 2.f);

	//_fixtureDef.shape = &_bodyShape;
	//_fixtureDef.density = 1.f;
	//_fixtureDef.friction = 1.f;
	//_fixtureDef.restitution = 1.f;
	//_fixtureDef.filter.groupIndex = -1;

	
}

bool Projectile::Update(sf::Event e, sf::Time dt)
{
	//_sprite.setRotation( MathHelper::RadianToDegree( _pBody->GetAngle() ) );

	_pBody->SetLinearVelocity(b2Vec2(3 * _direction, 0));

	_sprite.setPosition(
		MathHelper::ToPixel(_pBody->GetPosition().x),
		MathHelper::ToPixel(_pBody->GetPosition().y)
		);

	float distance = distanceTravelled();

	if (distance > _range)
	{
		return true;
	}
	else return false;
}

void Projectile::Draw(sf::RenderWindow& window, sf::Time dt)
{
	window.draw(_sprite);
}

Projectile::~Projectile()
{
}

float Projectile::distanceTravelled()
{
	float diff_x = abs(_pBody->GetPosition().x - _initpos.x);
	//float diff_y = abs(_pBody->GetPosition().y - _initpos.y);

	//return sqrt(diff_x*diff_x + diff_y*diff_y);
	return diff_x;
}

b2Body* Projectile::GetPhysicsBody() { return _pBody; }
