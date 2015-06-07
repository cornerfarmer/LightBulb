#include "Arrow.hpp"

Arrow::Arrow(sf::Vector2f startPos, sf::Vector2f endPos, std::string description)
{
	// Create a new VertexArray
	lines = sf::VertexArray(sf::PrimitiveType::Lines, 6);

	// Set the start to the position of the prevNeuron shape
	lines[0].position = startPos;
	// Set the start to the position of the nextNeuron shape
	lines[1].position = endPos;

	float angle = calcAngleFromLine(startPos, endPos);
	lines[2].position = endPos;
	lines[3].position = calcCartesianFromPolarCoordinates(endPos, 10, angle + M_PI + 0.6);

	lines[4].position = endPos;
    lines[5].position = calcCartesianFromPolarCoordinates(endPos, 10, angle + M_PI - 0.6);

	text.setFont(font);
	text.setString(description);
	text.setPosition(calcCartesianFromPolarCoordinates(startPos + sf::Vector2f((endPos.x - startPos.x) / 3, (endPos.y - startPos.y) / 3), 10, angle - M_PI / 2));    
	text.setCharacterSize(15);
	text.setRotation(angle / M_PI * 180);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
}

void Arrow::draw(sf::RenderWindow &window)
{
	window.draw(lines);
	window.draw(text);
}