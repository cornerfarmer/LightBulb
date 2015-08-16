#pragma once

#ifndef _NATUREDRAWER_H_
#define _NATUREDRAWER_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>
#include <map>

// Forward declarations
class Nature;

// This structure describes all options of an NatureDrawer
struct NatureDrawerOptions
{
	// Position
	int posX;
	int posY;
	// Zoom
	float scalingX;
	float scalingY;
	// Network
	Nature* nature;	

	NatureDrawerOptions()
	{
		posX = 0;
		posY = 0;
		scalingX = 10;
		scalingY = 10;
		nature = NULL;
	}
};

// A chart which visualizes the nature
class NatureDrawer : public GraphicObject
{
private:
	std::unique_ptr<NatureDrawerOptions> options;
	// This texture will contain the chart, calculated in recalculateAllValues
	std::vector<std::vector<sf::RectangleShape>> rectangles;
public:
	NatureDrawer(NatureDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif
