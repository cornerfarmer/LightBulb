#pragma once

#ifndef _ANIMAL_H_
#define _ANIMAL_H_

// Library Includes
#include <memory>

// Includes
#include "Learning\EvolutionObjectInterface.hpp"

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;
class RecurrentLayeredNetworkOptions;
class Nature;

class Animal : public EvolutionObjectInterface 
{
protected:
	NeuralNetwork* brain;
	Nature* nature;
	int posX;
	int posY;
	int dirX;
	int dirY;
	int health;
	bool dead;
	int stepsSurvived;
	void rotate(int dir);
public:	
	Animal(Nature* nature_, int posX_, int posY_, int dirX_, int dirY_);
	~Animal();
	void doNNCalculation(EvolutionLearningRule& learningRule);
	int getPosX();
	int getPosY();
	bool isDead();
	int getStepsSurvived();
	NeuralNetwork* getNeuralNetwork();
	void reset(int posX_, int posY_, int dirX_, int dirY_);
	EvolutionObjectInterface* clone();
};
#endif