#pragma once

#ifndef _EARTHTILE_H_
#define _EARTHTILE_H_

// Library Includes

// Includes
#include "Examples/Nature/AbstractTile.hpp"

// Forward declarations


class EarthTile : public AbstractTile
{
protected:	
	float food;
public:	
	EarthTile();
	//sf::Color getColor();
	float tryToEat() override;
	bool isWalkable() override;
	double getViewValue() override;
	const wxBrush* getColor() override;
};
#endif