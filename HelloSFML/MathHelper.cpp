#include "MathHelper.h"

const float MathHelper::unitToPixel = 50.0f;

const float MathHelper::pixelToUnit = 1 / unitToPixel;

MathHelper::MathHelper()
{
	std::cout << "Warn : Direct contructor invocation"; 
}

Vector2f MathHelper::ToUnit( Vector2f pixelCoord) { return pixelCoord * pixelToUnit;	}

Vector2f MathHelper::ToPixel( Vector2f unitCoord ) { return unitCoord * unitToPixel;	}

float MathHelper::ToPixel( float inUnit ) { return inUnit * unitToPixel;	}

float MathHelper::ToUnit( float inPixel) { return inPixel * pixelToUnit;	}

float MathHelper::DegreeToRadian( float inDegree )	{	return ( inDegree * b2_pi ) / 180.f;	}

float MathHelper::RadianToDegree( float inRadian )	{	return ( inRadian * 180.f ) / b2_pi;	}