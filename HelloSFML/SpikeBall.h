#pragma once
#include "ball.h"
#include <iostream>

using namespace std;

class SpikeBall :
	public Ball
{
public:
	SpikeBall();

	SpikeBall(sf::Texture& texture, float initX, float initY);
};

