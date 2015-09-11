// Includes
#include "Examples\TicTacToe.hpp"
#include "Examples\TicTacToeKI.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
//Library includes
#include <iostream>


EvolutionObjectInterface* TicTacToe::createNewObject()
{
	return new TicTacToeKI(this);
}

TicTacToe::TicTacToe()
{
	fields.resize(3);
	for (int x = 0; x < fields.size(); x++)
	{
		fields[x].resize(3);
	}
	resetWorld();

	window.create(sf::VideoMode(800, 700), "LightBulb!");
	TicTacToeDrawerOptions options;
	options.ticTacToe = this;
	displayMode = true;
	drawer.reset(new TicTacToeDrawer(options));
}

int TicTacToe::getFieldValue(int x, int y)
{
	return fields[x][y];
}

void TicTacToe::doSimulationStep(EvolutionLearningRule& learningRule)
{	
	points.clear();
	for (auto ki = objects.begin(); ki != objects.end(); ki++)
	{	
		for (auto otherKI = objects.begin(); otherKI != objects.end(); otherKI++)
		{
			if (*ki != *otherKI)
			{
				resetWorld();
				for (int i = 0; i < 9; i++)
				{
					sf::Event event;
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();
						else if (event.type == sf::Event::KeyPressed)
							displayMode = !displayMode;
					}

					if (displayMode) {
						window.clear();
						drawer->recalculateAllValues();
						drawer->draw(window);
						window.display();
					}

					if (i % 2 == 0)
					{
						currentPlayer = 1;
						(*ki)->doNNCalculation(learningRule);
					}
					else
					{
						currentPlayer = -1;
						(*otherKI)->doNNCalculation(learningRule);
					}
					if (whoHasWon() != 0)
						break;
				}				
				if (whoHasWon() == 1)
					points[static_cast<TicTacToeKI*>(*ki)]++;
				else if (whoHasWon() == -1)
					points[static_cast<TicTacToeKI*>(*otherKI)]++;
			}
		}
	}
}

bool TicTacToe::isFree(int x, int y)
{
	return fields[x][y] == 0;
}


int TicTacToe::whoHasWon()
{
	if (fields[0][0] != 0 && fields[0][0] == fields[0][1] && fields[0][1] == fields[0][2])
		return fields[0][0];
	else if (fields[1][0] != 0 && fields[1][0] == fields[1][1] && fields[1][1] == fields[1][2])
		return fields[1][0];
	else if (fields[2][0] != 0 && fields[2][0] == fields[2][1] && fields[2][1] == fields[2][2])
		return fields[2][0];

	else if (fields[0][0] != 0 && fields[0][0] == fields[1][0] && fields[1][0] == fields[2][0])
		return fields[0][0];
	else if (fields[0][1] != 0 && fields[0][1] == fields[1][1] && fields[1][1] == fields[2][1])
		return fields[0][1];
	else if (fields[0][2] != 0 && fields[0][2] == fields[1][2] && fields[1][2] == fields[2][2])
		return fields[0][2];

	else if (fields[0][0] != 0 && fields[0][0] == fields[1][1] && fields[1][1] == fields[2][2])
		return fields[0][0];
	else if (fields[2][0] != 0 && fields[2][0] == fields[1][1] && fields[1][1] == fields[0][2])
		return fields[2][0];
	else
		return 0;
}

void TicTacToe::setField(int x, int y)
{
	fields[x][y] = currentPlayer;
}

int TicTacToe::getScore(EvolutionObjectInterface* object)
{
	return points[static_cast<TicTacToeKI*>(object)];
}

void TicTacToe::resetWorld()
{
	for (auto column = fields.begin(); column != fields.end(); column++)
	{
		for (auto field = column->begin(); field != column->end(); field++)
		{
			*field = 0;
		}
	}
}


std::vector<double> TicTacToe::getSight()
{
	std::vector<double> sight;
	for (auto column = fields.begin(); column != fields.begin(); column++)
	{
		for (auto field = column->begin(); field != column->end(); field++)
		{
			if (currentPlayer == 1)
				sight.push_back(*field);
			else
				sight.push_back(-1 * *field);
		}
	}
	return sight;
}
