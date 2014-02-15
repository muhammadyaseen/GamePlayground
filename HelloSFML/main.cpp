#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>
#include "Game.h"
  
using namespace sf;
 
int main()
{
	
	RenderWindow gameWindow(VideoMode(800,800), "SFML + Box2D");

	SFMLDebugDraw debugDrawInstance(gameWindow);

	debugDrawInstance.SetFlags(b2Draw::e_shapeBit);

	Game *thisGame = new Game( gameWindow, debugDrawInstance );

	thisGame->Run();


	return 0;
}