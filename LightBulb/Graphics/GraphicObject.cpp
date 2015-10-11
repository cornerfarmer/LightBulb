// Includes
#include "Graphics/GraphicObject.hpp"
#include <iomanip>
#include <sstream>

sf::Font GraphicObject::font;

GraphicObject::GraphicObject()
{
	static bool fontIsEmpty = true;
	// If this is the first graphic objects which is created
	if (fontIsEmpty)
	{
		// Load the default font
		font.loadFromFile("Quicksand-Regular.ttf");
		fontIsEmpty = false;		
	}
}

float GraphicObject::calcAngleFromLine(sf::Vector2f lineStart, sf::Vector2f lineEnd)
{
    float angle;
	// If the end and start position have the same x coordinate
	if ((lineEnd.x - lineStart.x) == 0)
	{
		// Return 90 degree if endY > startY, else 270 degree
		if ((lineEnd.y-lineStart.y)>0)
			angle = (float)M_PI / 2;
		else
			angle = (float)M_PI / 2 * 3;
	}
	else
	{
		// Calculate the angle with the help of the tangens
		angle = atan((lineEnd.y - lineStart.y) / (lineEnd.x - lineStart.x));
		if (lineStart.x < lineEnd.x)
			angle = fmod(2 * (float)M_PI + angle, 2 * (float)M_PI);
		else
			angle = (float)M_PI + angle;     
	}
	return angle;
}

sf::Vector2f GraphicObject::calcCartesianFromPolarCoordinates(sf::Vector2f center, sf::Vector2f radiusVector, float angle)
{
	// Just use the unit circle calculation
	return sf::Vector2f(center.x + radiusVector.x * cos(angle), center.y + radiusVector.y * sin(angle));
}

sf::Vector2f GraphicObject::calcCartesianFromPolarCoordinates(sf::Vector2f center, float radius, float angle)
{
	return calcCartesianFromPolarCoordinates(center, sf::Vector2f(radius, radius), angle);
}

std::string GraphicObject::floatToString(const double value, const int precision)
{
	std::ostringstream out;
	out << std::setprecision(precision) << value;
	return out.str();
}
