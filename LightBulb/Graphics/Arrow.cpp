#include "Graphics\Arrow.hpp"

Arrow::Arrow(sf::Vector2f startPos, sf::Vector2f endPos, std::string description, sf::VertexArray extraLines)
{
	// Create a new VertexArray
	lines = sf::VertexArray(sf::Lines, 6);
	
	// Set the start to the position of the prevNeuron shape
	lines[0].position = startPos;
	// Set the start to the position of the nextNeuron shape
	lines[1].position = endPos;

	// Calc the angle of the line between start and endpos
    float angle = calcAngleFromLine(startPos, endPos);
	// Add the two lines which are located at the head if the line and which make the arrow look like an arrow
	lines[2].position = endPos;
	lines[3].position = calcCartesianFromPolarCoordinates(endPos, 10, angle + (float)M_PI + 0.6f);

	lines[4].position = endPos;
    lines[5].position = calcCartesianFromPolarCoordinates(endPos, 10, angle + (float)M_PI - 0.6f);

	// Append all optional additional extra lines
	for (unsigned int i = 0; i < extraLines.getVertexCount(); i++)
		lines.append(extraLines[i]);

	// Set the Style of the description text
	text.setFont(font);
	text.setString(description);
	text.setCharacterSize(15);
	text.setRotation((float)(angle / M_PI * 180));
	// Set its position directly next to the middle of the line
	text.setPosition(calcCartesianFromPolarCoordinates(startPos + sf::Vector2f((endPos.x - startPos.x) / 3, (endPos.y - startPos.y) / 3), 10, angle - (float)M_PI / 2));    
	
	// Calculate the bounds of the text and set its origin to the center
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
}

void Arrow::draw(sf::RenderWindow &window)
{
	// Draw the lines and the text
	window.draw(lines);
	window.draw(text);
}
