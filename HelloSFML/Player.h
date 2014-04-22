#pragma once
#include "GameCharacter.h"

class Player : public GameCharacter
{
private:
	bool _inAir;
	bool _hit;
	Health _health;
	bool _attack1Called;
	bool _attack2Called;
	bool _attack3Called;

	enum State {
		Idle,
		Walking,
		Running,
		Rising,
		Falling,
		Landing,
		Hurt,
		Dead,
		Attack1,
		Attack2,
		Attack3,
		Special
	};

	State _state;
	State _previousState;

	std::map<State, Animation> _animationBank;
	std::map<State, Texture> _textureBank;
	
	void handleEvent(Event currentEvent, Event oldEvent);
	void handleState();
	void changeSprite(State);
	void create(Texture& texture, float initX, float initY);

public:
	Player();
	Player(Texture& texture, float initX, float initY);

	void SetWorld(b2World& world);

	void LoadContent();
	void Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime);

	void Damage(int);

	State GetState();
	b2Body* GetPhysicsBody();
	bool IsAlive();
};
