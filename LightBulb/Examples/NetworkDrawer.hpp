#pragma once

#ifndef _NETWORKDRAWER_H_
#define _NETWORKDRAWER_H_

// Includes
#include "Graphics/GraphicObject.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <map>
#include <memory>

// Forward declarations
class NetworkSimulator;

// This structure describes all options of an NatureDrawer
struct NetworkDrawerOptions
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

	NetworkSimulator* networkSimulator;

	NetworkDrawerOptions()
	{
		posX = 0;
		posY = 0;
		width = 500;
		height = 500;
		networkSimulator = NULL;
		startX = 0;
		startY = 0;
		endX = 1;
		endY = 1;
	}
};

//
class NetworkDrawer : public GraphicObject
{
private:
	std::unique_ptr<NetworkDrawerOptions> options;
	// 
	sf::VertexArray connections;
	std::vector<sf::RectangleShape> consumerShapes;

	std::vector<sf::CircleShape> mutationStrengths;
public:
	NetworkDrawer(NetworkDrawerOptions &options_);
	// This method draws the calculated chart
	void draw(sf::RenderWindow &window);
	// This method recalculates the chart
	void recalculateAllValues();
};

#endif
