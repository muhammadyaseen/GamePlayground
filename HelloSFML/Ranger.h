#pragma once
#include "Enemy.h"
class Ranger :
	public Enemy
{
	bool _knifeExists;
	bool _knifeThrown;
	Projectile* _pKnife;
	Texture _knifeText;
	
	void handleState();
	void handleEvent(Event e, Player& player);
	void create(Texture&, float, float);
	void changeSprite(State _state);
public:
	Ranger();
	b2Body* GetPhysicsBody();
	void LoadContent(int x,int y);
	void Update(Event gameEvent, Player& player, Time dt, Time frameTime);
	void Draw(sf::RenderWindow& window, sf::Time dt);
};
