#include "GraphicObject.hpp"

sf::Font GraphicObject::font = sf::Font();

GraphicObject::GraphicObject()
{
	static bool fontIsEmpty = true;
	if (fontIsEmpty)
	{
		font.loadFromFile("Quicksand-Regular.ttf");
		fontIsEmpty = false;
	}
}

float GraphicObject::calcAngleFromLine(sf::Vector2f lineStart, sf::Vector2f lineEnd)
{
	float angle;
	if ((lineEnd.x - lineStart.x) == 0)
	{
		if ((lineEnd.y-lineStart.y)>0)
			angle = M_PI / 2;
		else
			angle = M_PI / 2 * 3;
	}
	else
	{
		angle = atan((lineEnd.y - lineStart.y) / (lineEnd.x - lineStart.x));
		if (lineStart.x < lineEnd.x)
			angle = fmod(2 * M_PI + angle, 2 * M_PI);
		else
			angle = M_PI + angle;     
	}
	return angle;
}

sf::Vector2f GraphicObject::calcCartesianFromPolarCoordinates(sf::Vector2f center, float radius, float angle)
{
	return sf::Vector2f(center.x + radius * cos(angle), center.y + radius * sin(angle));
}