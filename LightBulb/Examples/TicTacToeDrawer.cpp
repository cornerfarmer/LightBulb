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

	lines = sf::VertexArray(sf::Lines);

	lines.append(sf::Vertex(sf::Vector2f(options->width / 3, 0)));
	lines.append(sf::Vertex(sf::Vector2f(options->width / 3, options->height)));

	lines.append(sf::Vertex(sf::Vector2f(options->width / 3 * 2, 0)));
	lines.append(sf::Vertex(sf::Vector2f(options->width / 3 * 2, options->height)));

	lines.append(sf::Vertex(sf::Vector2f(0, options->height / 3)));
	lines.append(sf::Vertex(sf::Vector2f(options->width, options->height / 3)));

	lines.append(sf::Vertex(sf::Vector2f(0, options->height / 3 * 2)));
	lines.append(sf::Vertex(sf::Vector2f(options->width, options->height / 3 * 2)));
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

bool TicTacToeDrawer::handleMouseInputEvent(sf::Event &event)
{
	int col = (event.mouseButton.x - options->posX) / (options->width / 3);
	int row = (event.mouseButton.y - options->posY) / (options->height / 3);
	if (col >= 0 && col < 3 && row >= 0 && row < 3) {
		options->ticTacToe->setField(col, row);
		return true;
	}
	else
		return false;
}

void TicTacToeDrawer::draw(sf::RenderWindow &window)
{
	window.draw(lines);

	// Go through all rectangles and draw them
	for (auto signCol = signs.begin(); signCol != signs.end(); signCol++)
	{
		for (auto sign = signCol->begin(); sign != signCol->end(); sign++)
		{
			window.draw(*sign);
		}
	}
}


