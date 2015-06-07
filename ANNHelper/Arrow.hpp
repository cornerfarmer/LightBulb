#pragma once

#ifndef _ARROW_H_
#define _ARROW_H_

// Includes
#include "GraphicObject.hpp"
#include <SFML\Graphics.hpp>
#include <string>

// Forward declarations

class Arrow : public GraphicObject
{
private:
	sf::VertexArray lines;
	sf::Text text;
public:
	Arrow(sf::Vector2f startPos, sf::Vector2f endPos, std::string description);
	void draw(sf::RenderWindow &window);
};

#endif