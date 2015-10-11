// Includes
#include "Examples/TicTacToeDrawer.hpp"
#include "Examples/TicTacToe.hpp"
// Library includes
#include <exception>
#include <vector>

TicTacToeDrawer::TicTacToeDrawer(TicTacToeDrawerOptions& options_)
{
	options.reset(new TicTacToeDrawerOptions(options_));

	// Check if all given options are correct
	// Check if the given nature is valid
	if (options->ticTacToe == NULL)
		throw std::invalid_argument("The given ticTacToe is not valid");

	signs.resize(3, std::vector<sf::Text>(3));

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			signs[x][y].setFont(font);
			// Set the position from the position of the neurons in the structure
			signs[x][y].setPosition(x * options->width / 3, y * options->height / 3);
			// Sets the size of the rectangle depending of the zoom
			signs[x][y].setCharacterSize(40);
			signs[x][y].setColor(sf::Color::White);
		}
	}
}

void TicTacToeDrawer::recalculateAllValues()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			int value = options->ticTacToe->getFieldValue(x, y);
			signs[x][y].setString(value == 1 ? "X" : (value == 0 ? " " : "O"));
		}
	}
}

void TicTacToeDrawer::draw(sf::RenderWindow &window)
{
	// Go through all rectangles and draw them
	for (auto signCol = signs.begin(); signCol != signs.end(); signCol++)
	{
		for (auto sign = signCol->begin(); sign != signCol->end(); sign++)
		{
			window.draw(*sign);
		}
	}
}

