// Includes
#include "Examples/Nature/EarthTile.hpp"

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

const wxBrush* EarthTile::getColor()
{
	return food > 0 ? wxGREEN_BRUSH : wxBLACK_BRUSH;
}
