#include "Enemy.h"
#include <iostream>
#include <map>
#include <string>
#include "Ball.h"

using namespace std;
using namespace sf;

void Enemy::Damage(int amount)
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

void Enemy::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
}

Enemy::Enemy()
{
}
