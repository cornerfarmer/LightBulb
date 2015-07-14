#pragma once

#ifndef _ARROW_H_
#define _ARROW_H_

// Includes
#include "Graphics\GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <string>

// A graphical arrow with a description
class Arrow : public GraphicObject
{
private:
	// Holds all lines that describe the arrow
	sf::VertexArray lines;
	// A description text
	sf::Text text;
public:
	// Create a arrow from a start to an end position with optional extraLines and a description
	Arrow(sf::Vector2f startPos, sf::Vector2f endPos, std::string description, sf::VertexArray extraLines);
	// Inherited:
	void draw(sf::RenderWindow &window);
	// Sets a new description and recalculates the position of the text
	void setDescription(std::string description);

	void setColor(const sf::Color &color);
};

#endif