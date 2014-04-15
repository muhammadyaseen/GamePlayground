#pragma once
#include "GameCharacter.h"

class Player : public GameCharacter
{
private:
	bool _inAir;
	Health _health;

	enum State {
		Idle, 
		Walking, 
		Running,
		Rising, 
		Falling,
		Landing,
		Hurt,
		Dead
	};

	State _state;
	State _previousState;

	std::map<State, Animation> _animationBank;
	std::map<State, Texture> _textureBank;
	
	//Animation *_currentAnimation;
	//AnimatedSprite _animatedSprite;
	
	void handleEvent(Event currentEvent, Event oldEvent);
	void handleState();
	void changeSprite(State);
	void create(Texture& texture, float initX, float initY);
public:
	Player();
	Player(Texture& texture, float initX, float initY);

	void SetWorld(b2World& world);
	//void Create(Texture& texture, float initX, float initY);

	void LoadContent();
	void Update(sf::Event gameEvent, Event oldGameEvent, sf::Time dt, Time frameTime);

	void Damage(int);

	State GetState();
	b2Body* GetPhysicsBody();
	bool IsAlive();
};
