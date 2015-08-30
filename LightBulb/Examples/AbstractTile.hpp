#pragma once

#ifndef _ABSTRACTTILE_H_
#define _ABSTRACTTILE_H_

// Library Includes

// Includes
#include <SFML\Graphics.hpp>

// Forward declarations


class AbstractTile 
{
protected:	
public:	
	virtual sf::Color getColor() = 0;
	virtual float tryToEat() = 0;
	virtual bool isWalkable() = 0;
	virtual double getViewValue() = 0;
};
#endif