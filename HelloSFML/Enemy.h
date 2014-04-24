#pragma once
#include "GameCharacter.h"
#include "Player.h"
#include "Projectile.h"

class Enemy : public GameCharacter
{
protected:
	bool _inAir;
	bool _alive;
	bool _hit;
	bool _attackCalled;
	Health _health;
	int _damage;

	enum State {
		Idle,
		Walking,
		Running,
		Rising,
		Falling,
		Landing,
		Hurt,
		Dead,
		Attack
	};

	State _state;
	State _previousState;

	bool playerFound;
	int playerOnRight;

	std::map<State, Texture> _textureBank;
	std::map<State, Animation> _animationBank;
	Animation *_currentAnimation;
	AnimatedSprite _animatedSprite;

public:
	Enemy();
	void Damage(int);
	virtual void Draw(sf::RenderWindow& window, sf::Time dt);
};

