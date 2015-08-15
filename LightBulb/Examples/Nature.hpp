#pragma once

#ifndef _NATURE_H_
#define _NATURE_H_

// Library Includes
#include <vector>

// Include
#include "Learning\EvolutionWorldInterface.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;
class Animal;

class Nature : public EvolutionWorldInterface
{
	std::vector<Animal*> animals;
	std::vector<std::vector<bool>> plants;
	int width;
	int height;
	bool getViewValueOfPos(int posX, int posY);
public:
	Nature();
	EvolutionObjectInterface* addNewObject();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	std::vector<bool> getSight(int posX, int posY, int dirX, int dirY);
	void tryToEat(int posX, int posY);
	bool isTileFree(int posX, int posY);
};

#endif