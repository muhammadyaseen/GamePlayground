#include "SpikeBall.h"

SpikeBall::SpikeBall()
{
	cout << "paramless spikeball ctor" << endl;
}


SpikeBall::SpikeBall(sf::Texture& texture, float initX, float initY)
{
	cout << "paramized spikeball ctor" << endl;
	Ball::Ball(texture, initX, initY);
}
