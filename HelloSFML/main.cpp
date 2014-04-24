#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>
#include "Game.h"
#include <stdlib.h>
using namespace sf;
 
int main()
{
	
	
	RenderWindow gameWindow(VideoMode(900,700), "SFML + Box2D");//,sf::Style::Fullscreen);

	SFMLDebugDraw debugDrawInstance(gameWindow);

	debugDrawInstance.SetFlags(b2Draw::e_shapeBit);

	Game *thisGame = new Game( gameWindow, debugDrawInstance );

	thisGame->Run();


	return 0;
}