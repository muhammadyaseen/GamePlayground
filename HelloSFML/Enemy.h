#pragma once
#include "GameCharacter.h"
#include "Player.h"

class Enemy : public GameCharacter
{
protected:
	bool _inAir;
	bool _alive;
	bool _hit;
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
		Attacking
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
	void Draw(sf::RenderWindow& window, sf::Time dt);
};

