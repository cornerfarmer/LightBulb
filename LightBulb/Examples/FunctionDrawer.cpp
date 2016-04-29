// Includes
#include "Examples/FunctionDrawer.hpp"
#include "Examples/FunctionSimulator.hpp"
#include "Examples/Position.hpp"
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
	positions.resize(options->functionSimulator->getPopulationSize() + options->markedPositions.size());
	mutationStrengths.resize(options->functionSimulator->getPopulationSize());
	
	auto position = positions.begin();
	auto mutationStrength = mutationStrengths.begin();
	for (auto object = options->functionSimulator->getEvolutionObjects()->begin(); object != options->functionSimulator->getEvolutionObjects()->end(); object++, position++, mutationStrength++)
	{
		std::vector<float> objectPosition = dynamic_cast<Position*>(*object)->getPosition();
		std::vector<double> objectMutationStrength = *dynamic_cast<Position*>(*object)->getMutationStrength();
		sf::Vector2f graphicsPosition((objectPosition[0] - options->startX) / (options->endX - options->startX) * options->width - 1, (objectPosition[1] - options->startY) / (options->endY - options->startY) * options->height - 1);

		position->setPosition(graphicsPosition);
		position->setSize(sf::Vector2f(2, 2));
		position->setFillColor(sf::Color::White);

		mutationStrength->setPosition(graphicsPosition);
		mutationStrength->setRadius(1);
		mutationStrength->setScale(objectMutationStrength[0] / (options->startX - options->endX) * options->width, objectMutationStrength[1] / (options->startY - options->endY) * options->height);

		mutationStrength->setFillColor(sf::Color::Transparent);
		mutationStrength->setOutlineColor(sf::Color::White);
		mutationStrength->setOutlineThickness(0.1);
		mutationStrength->setOrigin(mutationStrength->getRadius(), mutationStrength->getRadius());
		mutationStrength->setPointCount(100);
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

	for (auto mutationStrength = mutationStrengths.begin(); mutationStrength != mutationStrengths.end(); mutationStrength++)
	{
		window.draw(*mutationStrength);
	}
}

