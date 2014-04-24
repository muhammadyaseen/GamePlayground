#include "State.h"


State::State(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World)
	: timeStep(1.0f/20.0f ),
	 _rWindow(window), 
	 _rSfmlDebugDraw(debugDraw),
	 _pWorld(World),
	 LState(Playing)
{
}





State::~State(void)
{
}
