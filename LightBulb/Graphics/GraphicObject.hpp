#pragma once

#ifndef _GRAPHICOBJECT_H_
#define _GRAPHICOBJECT_H_

#define _USE_MATH_DEFINES

// Includes
#include <SFML\Graphics.hpp>
#include <math.h>

// Forward declarations

// A basic shape for an graphical object
class GraphicObject
{
protected:
	// A static default font which can be used in all graphic objects
	static sf::Font font;
	// Two helper functions to convert coordinates
	sf::Vector2f calcCartesianFromPolarCoordinates(sf::Vector2f center, double radius, double angle);
	sf::Vector2f calcCartesianFromPolarCoordinates(sf::Vector2f center, sf::Vector2f radiusVector, double angle);
	// Calculate the angle of a line
	double calcAngleFromLine(sf::Vector2f lineStart, sf::Vector2f lineEnd);	
public:
	virtual ~GraphicObject() {}
	GraphicObject();
	// This method will be used to draw the whole graphics object on the given window
	virtual void draw(sf::RenderWindow &window) = 0;
};

#endif