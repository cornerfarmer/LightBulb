// Includes
#include "Examples/NatureDrawer.hpp"
#include "Examples/Nature.hpp"
#include "Examples/AbstractTile.hpp"
// Library includes
#include <exception>
#include <vector>

NatureDrawer::NatureDrawer(NatureDrawerOptions& options_)
{
	options.reset(new NatureDrawerOptions(options_));

	// Check if all given options are correct
	// Check if the given nature is valid
	if (options->nature == NULL)
		throw std::invalid_argument("The given somNetwork is not valid");

	rectangles.resize(options->nature->getWidth(), std::vector<sf::RectangleShape>(options->nature->getHeight()));

	for (int x = 0; x < options->nature->getWidth(); x++)
	{
		for (int y = 0; y < options->nature->getHeight(); y++)
		{
			// Set the position from the position of the neurons in the structure
			rectangles[x][y].setPosition(x * options->scalingX, y * options->scalingY);
			// Sets the size of the rectangle depending of the zoom
			rectangles[x][y].setSize(sf::Vector2f(options->scalingX, (int)options->scalingY));
		}
	}
}

void NatureDrawer::recalculateAllValues()
{	
	for (int x = 0; x < options->nature->getWidth(); x++)
	{
		for (int y = 0; y < options->nature->getHeight(); y++)
		{
			if (!options->nature->isTileFree(x, y))
				rectangles[x][y].setFillColor(sf::Color::Red);
			else
				rectangles[x][y].setFillColor(options->nature->getTile(x, y)->getColor());
		}
	}
}

void NatureDrawer::draw(sf::RenderWindow &window)
{	
	// Go through all rectangles and draw them
	for (auto rectangleCol = rectangles.begin(); rectangleCol != rectangles.end(); rectangleCol++)
	{
		for (auto rectangle = rectangleCol->begin(); rectangle != rectangleCol->end(); rectangle++)
		{
			window.draw(*rectangle);
		}
	}
}

