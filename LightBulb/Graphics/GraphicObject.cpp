#include "Graphics\GraphicObject.hpp"

sf::Font GraphicObject::font = sf::Font();

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

double GraphicObject::calcAngleFromLine(sf::Vector2f lineStart, sf::Vector2f lineEnd)
{
	double angle;
	// If the end and start position have the same x coordinate
	if ((lineEnd.x - lineStart.x) == 0)
	{
		// Return 90 degree if endY > startY, else 270 degree
		if ((lineEnd.y-lineStart.y)>0)
			angle = M_PI / 2;
		else
			angle = M_PI / 2 * 3;
	}
	else
	{
		// Calculate the angle with the help of the tangens
		angle = atan((lineEnd.y - lineStart.y) / (lineEnd.x - lineStart.x));
		if (lineStart.x < lineEnd.x)
			angle = fmod(2 * M_PI + angle, 2 * M_PI);
		else
			angle = M_PI + angle;     
	}
	return angle;
}

sf::Vector2f GraphicObject::calcCartesianFromPolarCoordinates(sf::Vector2f center, sf::Vector2f radiusVector, double angle)
{
	// Just use the unit circle calculation
	return sf::Vector2f(center.x + radiusVector.x * cos(angle), center.y + radiusVector.y * sin(angle));
}

sf::Vector2f GraphicObject::calcCartesianFromPolarCoordinates(sf::Vector2f center, double radius, double angle)
{
	return calcCartesianFromPolarCoordinates(center, sf::Vector2f(radius, radius), angle);
}