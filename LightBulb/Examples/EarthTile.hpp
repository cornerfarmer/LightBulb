#pragma once

#ifndef _EARTHTILE_H_
#define _EARTHTILE_H_

// Library Includes
#include <SFML/Graphics.hpp>

// Includes
#include "Examples/AbstractTile.hpp"

// Forward declarations


class EarthTile : public AbstractTile
{
protected:	
	float food;
public:	
	EarthTile();
	sf::Color getColor();
	float tryToEat();
	bool isWalkable();
	double getViewValue();
};
#endif