#pragma once

#ifndef _TICTACTOEDRAWER_H_
#define _TICTACTOEDRAWER_H_

// Includes
#include "Graphics/GraphicObject.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <map>
#include <memory>

// Forward declarations
class TicTacToe;

// This structure describes all options of an NatureDrawer
struct TicTacToeDrawerOptions
{
	// Position
	int posX;
	int posY;

	float width;
	float height;

	TicTacToe* ticTacToe;

	TicTacToeDrawerOptions()
	{
		posX = 0;
		posY = 0;
		width = 500;
		height = 500;
		ticTacToe = NULL;
	}
};

// A chart which visualizes the nature
class TicTacToeDrawer : public GraphicObject
{
private:
	std::unique_ptr<TicTacToeDrawerOptions> options;
	// This texture will contain the chart, calculated in recalculateAllValues
	std::vector<std::vector<sf::Text>> signs;
public:
	TicTacToeDrawer(TicTacToeDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif
