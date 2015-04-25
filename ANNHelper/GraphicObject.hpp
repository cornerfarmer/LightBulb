#pragma once

#ifndef _GRAPHICOBJECT_H_
#define _GRAPHICOBJECT_H_

// Includes
#include <SFML\Graphics.hpp>

// Forward declarations

// A basic shape for an graphical object
class GraphicObject
{
protected:
	// These standad variables will contain the position of the object in pixels
	int posX;
	int posY;
public:
	virtual ~GraphicObject() {}
	GraphicObject(int posX_, int posY_);
	// This method will be used to draw the whole graphics object on the given window
	virtual void draw(sf::RenderWindow &window) = 0;
};

#endif