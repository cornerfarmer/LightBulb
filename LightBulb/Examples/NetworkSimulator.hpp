#pragma once

#ifndef _NETWORKSIMULATOR_H_
#define _NETWORKSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;

class NetworkSimulator : public AbstractSimpleEvolutionWorld
{
protected:
	std::vector<std::vector<float>> consumers;
	bool enableGraphics;
	AbstractEvolutionObject* createNewObject();
	//sf::RenderWindow window;
	//std::unique_ptr<NetworkDrawer> drawer;
	double distanceBetweenPositions(std::vector<float>& pos1, std::vector<float>& pos2);
public:
	NetworkSimulator(bool enableGraphics_, std::vector<std::vector<float>> consumers_);
	bool doSimulationStep();
	double getScore(AbstractEvolutionObject* object);
	std::vector<std::vector<float>>* getConsumers();
};

#endif
