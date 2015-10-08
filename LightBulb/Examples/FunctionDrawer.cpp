// Includes
#include "Examples\FunctionDrawer.hpp"
#include "Examples\FunctionSimulator.hpp"
#include "Examples\Position.hpp"
// Library includes
#include <exception>
#include <vector>

FunctionDrawer::FunctionDrawer(FunctionDrawerOptions& options_)
{
	options.reset(new FunctionDrawerOptions(options_));

	// Check if all given options are correct
	// Check if the given nature is valid
	if (options->functionSimulator == NULL)
		throw std::invalid_argument("The given functionSimulator is not valid");	
}

void FunctionDrawer::recalculateAllValues()
{
	positions.resize(options->functionSimulator->getEvolutionObjects()->size() + options->markedPositions.size());
	
	auto position = positions.begin();
	for (auto object = options->functionSimulator->getEvolutionObjects()->begin(); object != options->functionSimulator->getEvolutionObjects()->end(); object++, position++)
	{
		std::vector<float> objectPosition = dynamic_cast<Position*>(*object)->getPosition();
		position->setPosition((objectPosition[0] - options->startX) / (options->endX - options->startX) * options->width - 1, (objectPosition[1] - options->startY) / (options->endY - options->startY) * options->height - 1);
		position->setSize(sf::Vector2f(2, 2));
		position->setFillColor(sf::Color::White);
	}

	
	for (auto markedPositon = options->markedPositions.begin(); markedPositon != options->markedPositions.end(); markedPositon++, position++)
	{
		position->setPosition((markedPositon->x - options->startX) / (options->endX - options->startX) * options->width - 2, (markedPositon->y - options->startY) / (options->endY - options->startY) * options->height - 2);
		position->setSize(sf::Vector2f(4, 4));
		position->setFillColor(sf::Color::Yellow);
	}

}

void FunctionDrawer::draw(sf::RenderWindow &window)
{
	// Outline the part of the window which will contain our chart
	sf::RectangleShape drawRect;
	drawRect.setPosition((float)options->posX, (float)options->posY);
	drawRect.setSize(sf::Vector2f((float)options->width, (float)options->height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all rectangles and draw them
	for (auto position = positions.begin(); position != positions.end(); position++)
	{
		window.draw(*position);
	}
}

