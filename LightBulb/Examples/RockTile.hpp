#pragma once

#ifndef _ROCKTILE_H_
#define _ROCKTILE_H_

// Library Includes
#include <SFML/Graphics.hpp>

// Includes
#include "Examples/AbstractTile.hpp"

// Forward declarations


class RockTile : public AbstractTile
{
protected:	
public:	
	sf::Color getColor();
	float tryToEat();
	bool isWalkable();
	double getViewValue();
};
#endif