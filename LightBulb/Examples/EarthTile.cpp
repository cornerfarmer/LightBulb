// Includes
#include "Examples\EarthTile.hpp"

sf::Color EarthTile::getColor()
{
	return food > 0 ? sf::Color::Green : sf::Color::Black;
}

float EarthTile::tryToEat()
{
	float foodPrev = food;
	food = 0;
	return foodPrev;
}

bool EarthTile::isWalkable()
{
	return true;
}

EarthTile::EarthTile()
{
	food = 4;
}

double EarthTile::getViewValue()
{
	return food > 0 ? 10 : 5;
}