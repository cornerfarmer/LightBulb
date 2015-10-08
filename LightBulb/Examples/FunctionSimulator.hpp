#pragma once

#ifndef _FUNCTIONSIMULATOR_H_
#define _FUNCTIONSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>
#include <SFML\Graphics.hpp>

// Include
#include "Learning\Evolution\AbstractSimpleEvolutionWorld.hpp"
#include "Examples\FunctionDrawer.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class AbstractTile;

class FunctionSimulator : public AbstractSimpleEvolutionWorld
{
protected:
	AbstractEvolutionObject* createNewObject();
	sf::RenderWindow window;
	std::unique_ptr<FunctionDrawer> drawer;
public:
	FunctionSimulator();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	double getScore(AbstractEvolutionObject* object);
};

#endif