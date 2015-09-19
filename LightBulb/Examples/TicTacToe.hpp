#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <map>
#include <SFML\Graphics.hpp>

// Include
#include "Learning\AbstractSimpleEvolutionWorld.hpp"
#include "Examples\TicTacToeDrawer.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;
class TicTacToeKI;
class AbstractTile;

class TicTacToe : public AbstractSimpleEvolutionWorld
{
protected:
	std::vector<std::vector<int>> fields;	
	std::map<TicTacToeKI*, int> points;
	EvolutionObjectInterface* createNewObject();
	sf::RenderWindow window;
	std::unique_ptr<TicTacToeDrawer> drawer;
	void resetWorld();
	int whoHasWon();
	int currentPlayer;
	bool displayMode;
	bool illegalMove;
public:
	TicTacToe();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	std::vector<double> getSight();
	void setField(int x, int y);
	int getScore(EvolutionObjectInterface* object);	
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	void rateBestKI(EvolutionLearningRule& learningRule);
	void setIllegalMove(bool illegalMove_);
};

#endif