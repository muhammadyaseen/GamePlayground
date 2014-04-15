#pragma once
#include "Enemy.h"
class Ranger :
	public Enemy
{
	void handleState();
	void handleEvent(Event e, Player& player);
	void create(Texture&, float, float);
	void changeSprite(State _state);
public:
	Ranger();
	void LoadContent();
	void Update(Event gameEvent, Player& player, Time dt, Time frameTime);
};
