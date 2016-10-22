// Includes
#include "Examples/Nature/RockTile.hpp"


float RockTile::tryToEat()
{
	return 0;
}

bool RockTile::isWalkable()
{
	return false;
}

double RockTile::getViewValue()
{
	return 0;
}

const wxBrush& RockTile::getColor()
{
	return *wxGREY_BRUSH;
}
