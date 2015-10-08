#pragma once

#ifndef _FUNCTIONDRAWER_H_
#define _FUNCTIONDRAWER_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <math.h>
#include <map>

// Forward declarations
class FunctionSimulator;

// This structure describes all options of an NatureDrawer
struct FunctionDrawerOptions
{
	// Position
	int posX;
	int posY;

	float width;
	float height;

	float startX;
	float endX;
	float startY;
	float endY;

	std::vector<sf::Vector2f> markedPositions;

	FunctionSimulator* functionSimulator;

	FunctionDrawerOptions()
	{
		posX = 0;
		posY = 0;
		width = 500;
		height = 500;
		functionSimulator = NULL;
		startX = 0;
		startY = 0;
		endX = 1;
		endY = 1;
	}
};

//
class FunctionDrawer : public GraphicObject
{
private:
	std::unique_ptr<FunctionDrawerOptions> options;
	// 
	std::vector<sf::RectangleShape> positions;
public:
	FunctionDrawer(FunctionDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif
