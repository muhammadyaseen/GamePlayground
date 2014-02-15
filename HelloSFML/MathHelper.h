#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

//namespace MathHelper 
class MathHelper
{
private:
	MathHelper();

public:
	//Arbitary assumption for Box2D coordinates conversion

	//Box2D uses MKS system

	//In game we normally talk in pixels

	static const float unitToPixel;// = 32.0f;					    
	static const float pixelToUnit;// = 1 / unitToPixel;
	
	static Vector2f ToUnit( Vector2f pixelCoord); //{ return pixelCoord * pixelToUnit;	}
	static Vector2f ToPixel( Vector2f unitCoord );// { return unitCoord * unitToPixel;	}
	static float ToPixel( float inUnit ); //{ return inUnit * unitToPixel;	}
	static float ToUnit( float inPixel); //{ return inPixel * pixelToUnit;	}
	static float DegreeToRadian( float inDegree );	//{	return ( inDegree * b2_pi ) / 180.f;	}
	static float RadianToDegree( float inRadian );	//{	return ( inRadian * 180.f ) / b2_pi;	}

};




