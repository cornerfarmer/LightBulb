#pragma once

#ifndef _ROCKTILE_H_
#define _ROCKTILE_H_

// Library Includes

// Includes
#include "Examples/AbstractTile.hpp"

// Forward declarations


class RockTile : public AbstractTile
{
protected:	
public:	
	//sf::Color getColor();
	float tryToEat() override;
	bool isWalkable() override;
	double getViewValue() override;
};
#endif