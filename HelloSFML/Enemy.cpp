#include "Enemy.h"
#include <iostream>
#include <map>
#include <string>
#include "Ball.h"

using namespace std;
using namespace sf;

void Enemy::Damage(int amount)
{
	_health -= amount;
	// TODO: Change state to Hurt
}

void Enemy::Draw(RenderWindow& window, Time dt)
{
	window.draw(_animatedSprite);
}

Enemy::Enemy()
{
}
